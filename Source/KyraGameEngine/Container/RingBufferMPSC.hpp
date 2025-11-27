/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2025 KyraGameEngine authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KYRAGAMEENGINE_CONTAINER_RINGBUFFERMPSC_HPP
#define KYRAGAMEENGINE_CONTAINER_RINGBUFFERMPSC_HPP

#include <memory>
#include <atomic>
#include <array>
#include <type_traits>
#include <utility>
#include <assert.h>

namespace kyra {

    /**
     * @file RingBufferMPSC.hpp
     * @brief Multiple-producer single-consumer (MPSC) lock-free ring buffer.
     *
     * This container implements a bounded, lock-free MPSC ring buffer based on
     * Dmitry Vyukov's bounded MPMC queue algorithm adapted for the MPSC use
     * case. It allows multiple producers to concurrently enqueue items without
     * a mutex while a single consumer dequeues items. Elements are stored in
     * raw aligned storage and are constructed/destructed in-place.
     *
     * Requirements & guarantees:
     * - `init(capacity)` must be called with a power-of-two `capacity >= 2`
     *   before using the queue.
     * - The queue is lock-free (no mutexes) but not wait-free.
     * - Producers are safe to call concurrently. Only a single consumer may
     *   call `pop` concurrently.
     * - The destructor will attempt to destroy remaining constructed elements
     *   but the queue must be quiesced (no concurrent producers/consumer)
     *   when being destroyed to avoid races.
     * - `size()` and `empty()` are approximate under concurrent use.
     *
     * Exception-safety:
     * - `push`/`emplace` publish a slot only after construction completes,
     *   so constructor exceptions do not corrupt the queue.
     * - `pop` moves the element into the caller-provided storage and then
     *   destroys the object in the slot. If the move/copy throws, queue
     *   invariants may be violated; prefer noexcept-moveable types in
     *   concurrent contexts.
     */

     /**
      * @class RingBufferMPSC
      * @brief Lock-free MPSC ring buffer storing objects of type `Type`.
      *
      * Template parameter:
      * - `Type` : element type stored in the queue.
      */
    template<class Type>
    class RingBufferMPSC {
        using Storage = typename std::aligned_storage<sizeof(Type), alignof(Type)>::type;

        /**
         * @struct Cell
         * @brief Single slot in the ring buffer.
         *
         * Each cell contains an atomic sequence used to determine the slot's
         * state (free, ready for enqueue, or ready for dequeue) and raw
         * storage for the element. Sequence values encode the expected
         * position to avoid ABA issues and to coordinate producers/consumer.
         */
        struct Cell {
            std::atomic<size_t> sequence;
            Storage storage;
        };

        std::unique_ptr<Cell[]> m_Cells;    ///< Array of cells (size = capacity)
        std::size_t m_Capacity = 0;         ///< Configured capacity (power of two)
        std::size_t m_Mask = 0;             ///< Mask for index wrapping (capacity - 1)

        // head = enqueue position, tail = dequeue position
        alignas(64) std::atomic<size_t> m_Head{ 0 };
        static constexpr size_t pad_bytes = (64 > sizeof(std::atomic<size_t>)) ? (64 - sizeof(std::atomic<size_t>)) : 0;
        std::array<char, pad_bytes> pad1{};
        alignas(64) std::atomic<size_t> m_Tail{ 0 };
        std::array<char, pad_bytes> pad2{};

        bool m_IsInitialized = false;       ///< Whether `init()` has been called

        /**
         * @brief Get pointer to the cell for a logical index (masked).
         * @param index Logical index (unmasked)
         * @return Pointer to `Cell` corresponding to the index masked by m_Mask
         */
        Cell* cellPtr(std::size_t index) noexcept {
            return &m_Cells[index & m_Mask];
        }

    public:
        RingBufferMPSC(const RingBufferMPSC&) = delete;
        RingBufferMPSC& operator=(const RingBufferMPSC&) = delete;
        RingBufferMPSC() = default;

        /**
         * @brief Destructor.
         *
         * Attempts to destroy any constructed elements remaining in the queue.
         * The queue must be quiesced (no concurrent producers or consumer)
         * during destruction to avoid undefined behavior.
         */
        ~RingBufferMPSC() {
            if (m_IsInitialized && m_Cells) {
                // Destroy any constructed objects between tail and head.
                size_t head = m_Head.load(std::memory_order_acquire);
                size_t tail = m_Tail.load(std::memory_order_acquire);
                for (size_t pos = tail; pos != head; ++pos) {
                    Cell* c = cellPtr(pos);
                    size_t seq = c->sequence.load(std::memory_order_relaxed);
                    if (seq == pos + 1) {
                        Type* p = reinterpret_cast<Type*>(&c->storage);
                        p->~Type();
                    }
                }
            }
        }

        /**
         * @brief Initialize the ring buffer with a given capacity.
         * @param capacity Capacity must be a power of two and >= 2.
         *
         * Allocates internal storage and initializes per-slot sequence values
         * required by the algorithm.
         */
        void init(std::size_t capacity) {
            assert(capacity >= 2 && (capacity & (capacity - 1)) == 0 && "capacity must be power of two >= 2");
            m_Cells.reset(new Cell[capacity]);
            m_Capacity = capacity;
            m_Mask = capacity - 1;
            for (std::size_t i = 0; i < capacity; ++i) {
                m_Cells[i].sequence.store(i, std::memory_order_relaxed);
            }
            m_Head.store(0, std::memory_order_relaxed);
            m_Tail.store(0, std::memory_order_relaxed);
            m_IsInitialized = true;
        }

        /**
         * @brief Check whether the buffer has been initialized.
         * @return true if `init()` has been called.
         */
        constexpr bool isInitialized() const noexcept { return m_IsInitialized; }

        /**
         * @brief Internal push helper that forwards the provided value into
         *        the queue using placement-new.
         * @tparam U Deducted type for forwarding.
         * @param item Value to enqueue (forwarded).
         * @return true on success, false if queue is full or not initialized.
         *
         * This function is lock-free. It attempts to claim a slot by reading
         * the slot's sequence and performing a CAS on `m_Head`. The element
         * is constructed in-place and the sequence is published after
         * construction completes, ensuring producers do not expose a
         * partially-constructed element to the consumer.
         */
        template<class U>
        bool internalPush(U&& item) {
            if (!m_IsInitialized) return false;
            size_t pos = m_Head.load(std::memory_order_relaxed);
            for (;;) {
                Cell* c = cellPtr(pos);
                size_t seq = c->sequence.load(std::memory_order_acquire);
                intptr_t dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos);
                if (dif == 0) {
                    if (m_Head.compare_exchange_weak(pos, pos + 1, std::memory_order_acq_rel, std::memory_order_relaxed)) {
                        // We own this slot; construct in-place
                        new (&c->storage) Type(std::forward<U>(item));
                        // Publish the slot for the consumer
                        c->sequence.store(pos + 1, std::memory_order_release);
                        return true;
                    }
                    // CAS failed; pos updated with current head — retry
                }
                else if (dif < 0) {
                    // sequence < pos -> slot not yet free, queue full
                    return false;
                }
                else {
                    // Another producer has moved head forward; reload
                    pos = m_Head.load(std::memory_order_relaxed);
                }
            }
        }

        /**
         * @brief Push rvalue into the queue.
         * @param item Rvalue to push.
         * @return true on success, false if full or not initialized.
         */
        bool push(Type&& item) { return internalPush(std::move(item)); }

        /**
         * @brief Push const-lvalue into the queue.
         * @param item Const-lvalue reference to push.
         * @return true on success, false if full or not initialized.
         */
        bool push(const Type& item) { return internalPush(item); }

        /**
         * @brief Emplace-construct an element into the queue.
         * @tparam Args Constructor argument types.
         * @param args Constructor arguments forwarded to `Type`.
         * @return true on success, false if full or not initialized.
         *
         * Declared `noexcept` when `Type` is nothrow-constructible from
         * `Args...`. The slot is published only after construction
         * completes, preserving queue invariants on constructor failure.
         */
        template<class... Args>
        bool emplace(Args&&... args) noexcept(std::is_nothrow_constructible<Type, Args...>::value) {
            if (!m_IsInitialized) return false;
            size_t pos = m_Head.load(std::memory_order_relaxed);
            for (;;) {
                Cell* c = cellPtr(pos);
                size_t seq = c->sequence.load(std::memory_order_acquire);
                intptr_t dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos);
                if (dif == 0) {
                    if (m_Head.compare_exchange_weak(pos, pos + 1, std::memory_order_acq_rel, std::memory_order_relaxed)) {
                        new (&c->storage) Type(std::forward<Args>(args)...);
                        c->sequence.store(pos + 1, std::memory_order_release);
                        return true;
                    }
                }
                else if (dif < 0) {
                    return false; // full
                }
                else {
                    pos = m_Head.load(std::memory_order_relaxed);
                }
            }
        }

        /**
         * @brief Pop an element from the queue.
         * @param msg Reference where the popped element will be assigned (moved).
         * @return true on success, false if empty or not initialized.
         *
         * The consumer moves the element into `msg`, destroys the original
         * object in the slot, and then updates the sequence to mark the slot
         * as free for producers. If the move throws, the queue state may be
         * left inconsistent; prefer noexcept move types in concurrent contexts.
         */
        bool pop(Type& msg) {
            if (!m_IsInitialized) return false;
            size_t pos = m_Tail.load(std::memory_order_relaxed);
            for (;;) {
                Cell* c = cellPtr(pos);
                size_t seq = c->sequence.load(std::memory_order_acquire);
                intptr_t dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos + 1);
                if (dif == 0) {
                    if (m_Tail.compare_exchange_weak(pos, pos + 1, std::memory_order_acq_rel, std::memory_order_relaxed)) {
                        Type* p = reinterpret_cast<Type*>(&c->storage);
                        msg = std::move(*p);
                        p->~Type();
                        // mark slot as free for future producers
                        c->sequence.store(pos + m_Capacity, std::memory_order_release);
                        return true;
                    }
                }
                else if (dif < 0) {
                    return false; // empty
                }
                else {
                    pos = m_Tail.load(std::memory_order_relaxed);
                }
            }
        }

        /**
         * @brief Check whether the queue is empty.
         * @return true if empty or not initialized.
         */
        bool empty() const noexcept {
            if (!m_IsInitialized) return true;
            size_t tail = m_Tail.load(std::memory_order_acquire);
            size_t head = m_Head.load(std::memory_order_acquire);
            return tail == head;
        }

        /**
         * @brief Get the configured capacity.
         * @return The number of slots allocated for the queue.
         */
        constexpr std::size_t capacity() const noexcept { return m_Capacity; }

        /**
         * @brief Approximate number of elements currently stored.
         * @return Size (may be racy if producers/consumer run concurrently).
         */
        std::size_t size() const noexcept {
            if (!m_IsInitialized) return 0;
            size_t head = m_Head.load(std::memory_order_acquire);
            size_t tail = m_Tail.load(std::memory_order_acquire);
            return head - tail;
        }
    };
}

#endif