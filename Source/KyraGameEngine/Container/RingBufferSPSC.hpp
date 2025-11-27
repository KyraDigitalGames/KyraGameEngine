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

#ifndef KYRAGAMEENGINE_CONTAINER_RINGBUFFER_HPP
#define KYRAGAMEENGINE_CONTAINER_RINGBUFFER_HPP

#include <memory>
#include <atomic>
#include <array>
#include <type_traits>
#include <utility>
#include <assert.h>

namespace kyra {

	/**
	 * @file RingBufferSPSC.hpp
	 * @brief A single-producer single-consumer lock-free ring buffer container.
	 *
	 * This ring buffer stores objects of type `Type` in an internal raw storage
	 * area and constructs/destructs them in-place. The capacity must be a power
	 * of two and at least 2. The buffer uses atomic indices for `head` and
	 * `tail` so that one producer thread can safely push and one consumer thread
	 * can safely pop without locks (SPSC).
	 *
	 * Usage:
	 * - Call `init(capacity)` with a power-of-two capacity >= 2 before use.
	 * - Use `push`, `emplace` for producer-side insertion.
	 * - Use `pop` for consumer-side removal.
	 *
	 * Note:
	 * - `size()` is approximate when producers/consumers operate concurrently.
	 * - The class is non-copyable.
	 */

	 /**
	  * @class RingBuffer
	  * @brief Lock-free SPSC ring buffer storing objects of type `Type`.
	  *
	  * Template parameter:
	  * - `Type` : element type stored in the buffer.
	  */
	template<class Type>
	class RingBufferSPSC {

		// Storage for one element, properly aligned for `Type`.
		using Storage = typename std::aligned_storage<sizeof(Type), alignof(Type)>::type;

		std::unique_ptr<Storage[]> m_Storage;
		std::size_t m_Capacity = 0;
		std::size_t m_Mask = 0;

		// Align head/tail to separate cache lines to reduce false sharing.
		alignas(64) std::atomic<size_t> m_Tail{ 0 };
		static constexpr size_t pad_bytes = (64 > sizeof(std::atomic<size_t>)) ? (64 - sizeof(std::atomic<size_t>)) : 0;
		std::array<char, pad_bytes> pad1{};
		alignas(64) std::atomic<size_t> m_Head{ 0 };
		std::array<char, pad_bytes> pad2{};

		// Whether `init()` has been called and storage is allocated.
		bool m_IsInitialized = false;

		/**
		 * @brief Get a typed pointer to the slot at `index`.
		 * @param index Index into the internal storage array.
		 * @return Pointer to `Type` at the given slot.
		 *
		 * This does not perform any bounds checks and assumes the caller
		 * uses indices in the valid range [0, m_Capacity).
		 */
		Type* slotPtr(std::size_t index) noexcept {
			return reinterpret_cast<Type*>(&m_Storage[index]);
		}

		/**
		 * @brief Internal helper to push an item (unified rvalue/lvalue handling).
		 * @tparam U Deducted type for forwarding.
		 * @param item Item to insert (forwarded).
		 * @return true on success, false if buffer not initialized or full.
		 *
		 * This performs a placement-new into the slot. If the constructor throws,
		 * the head index is not published, preserving buffer consistency.
		 */
		template<class U>
		bool internalPush(U&& item) {
			if (!m_IsInitialized) {
				return false;
			}
			size_t head = m_Head.load(std::memory_order_relaxed);
			size_t next = (head + 1) & m_Mask;
			if (next == m_Tail.load(std::memory_order_acquire)) {
				return false; // full
			}
			// placement-new into slot; if ctor throws, head is not published
			new (slotPtr(head)) Type(std::forward<U>(item));
			m_Head.store(next, std::memory_order_release);
			return true;
		}

	public:
		RingBufferSPSC(const RingBufferSPSC&) = delete;
		RingBufferSPSC& operator=(const RingBufferSPSC&) = delete;

		/**
		 * @brief Default constructor.
		 * Object must be initialized via `init()` before use.
		 */
		RingBufferSPSC() = default;

		/**
		 * @brief Destructor.
		 * Destroys any constructed elements that remain in the buffer.
		 */
		~RingBufferSPSC() {
			// destroy any constructed objects
			if (m_IsInitialized && m_Storage) {
				size_t head = m_Head.load(std::memory_order_acquire);
				size_t tail = m_Tail.load(std::memory_order_acquire);
				while (tail != head) {
					Type* p = slotPtr(tail);
					p->~Type();
					tail = (tail + 1) & m_Mask;
				}
			}
		}

		/**
		 * @brief Initialize the ring buffer with a given capacity.
		 * @param capacity Capacity must be a power of two and >= 2.
		 *
		 * Allocates raw storage and resets indices. Calling `init` more than
		 * once will reallocate storage and reset the buffer state.
		 */
		void init(std::size_t capacity) {
			assert(capacity >= 2 && (capacity & (capacity - 1)) == 0 && "capacity must be power of two >= 2");
			m_Storage.reset(new Storage[capacity]);
			m_Capacity = capacity;
			m_Mask = capacity - 1;
			m_Head.store(0, std::memory_order_relaxed);
			m_Tail.store(0, std::memory_order_relaxed);
			m_IsInitialized = true;
		}

		/**
		 * @brief Check whether the buffer has been initialized.
		 * @return true if `init()` has been called.
		 */
		constexpr bool isInitialized() const noexcept {
			return m_IsInitialized;
		}


		/**
		 * @brief Push an rvalue into the buffer.
		 * @param item Rvalue item to push.
		 * @return true on success, false if full or not initialized.
		 */
		bool push(Type&& item) {
			return internalPush(std::move(item));
		}

		/**
		 * @brief Push a const-lvalue into the buffer.
		 * @param item Const-lvalue reference to push.
		 * @return true on success, false if full or not initialized.
		 */
		bool push(const Type& item) {
			return internalPush(item);
		}

		/**
		 * @brief Emplace-construct an element in-place.
		 * @tparam Args Constructor argument types.
		 * @param args Constructor arguments forwarded to `Type`.
		 * @return true on success, false if full or not initialized.
		 *
		 * The function is declared `noexcept` when `Type` is nothrow-constructible
		 * from `Args...`.
		 */
		template<class... Args>
		bool emplace(Args&&... args) noexcept(std::is_nothrow_constructible<Type, Args...>::value) {
			if (!m_IsInitialized) {
				return false;
			}
			size_t head = m_Head.load(std::memory_order_relaxed);
			size_t next = (head + 1) & m_Mask;
			if (next == m_Tail.load(std::memory_order_acquire)) {
				return false; // full
			}
			new (slotPtr(head)) Type(std::forward<Args>(args)...);
			m_Head.store(next, std::memory_order_release);
			return true;
		}

		/**
		 * @brief Pop an element from the buffer.
		 * @param msg Reference where the popped element will be assigned (moved).
		 * @return true on success, false if empty or not initialized.
		 *
		 * The element in the slot is moved into `msg` and then destroyed.
		 */
		bool pop(Type& msg) {
			if (!m_IsInitialized) {
				return false;
			}
			size_t tail = m_Tail.load(std::memory_order_relaxed);
			if (tail == m_Head.load(std::memory_order_acquire)) {
				return false; // empty
			}
			Type* p = slotPtr(tail);
			msg = std::move(*p);
			p->~Type();
			m_Tail.store((tail + 1) & m_Mask, std::memory_order_release);
			return true;
		}

		/**
		 * @brief Check whether the buffer is empty.
		 * @return true if empty or not initialized.
		 */
		bool empty() const noexcept {
			if (!m_IsInitialized) { return true; }
			return m_Tail.load(std::memory_order_acquire) == m_Head.load(std::memory_order_acquire);
		}

		/**
		 * @brief Get the configured capacity.
		 * @return The number of slots allocated for the buffer.
		 */
		constexpr std::size_t capacity() const noexcept {
			return m_Capacity;
		}

		/**
		 * @brief Approximate number of elements currently stored.
		 * @return Size (may be racy if producers/consumers run concurrently).
		 */
		std::size_t size() const noexcept {
			if (!m_IsInitialized) {
				return 0;
			}
			size_t head = m_Head.load(std::memory_order_acquire);
			size_t tail = m_Tail.load(std::memory_order_acquire);
			return (head + m_Capacity - tail) & m_Mask;
		}

	};
}

#endif