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

#ifndef KYRAGAMEENGINE_LOG_LOGGER_HPP
#define KYRAGAMEENGINE_LOG_LOGGER_HPP

/**
 * @file Logger.hpp
 * @brief Asynchronous, multi-producer single-consumer file logger.
 *
 * @details
 * The `kyra::Logger` class provides an asynchronous logging facility intended
 * primarily for game engine use where many threads may emit log messages but
 * only a single background thread writes them to disk. Producers push
 * `LogMessage` objects into a lock-free ring buffer (MPSC) and notify the
 * consumer thread. The consumer thread drains messages and writes them to a
 * file.
 *
 * Important semantics:
 * - start() must be called before any logging occurs to initialize the ring buffer
 *   and launch the worker thread.
 * - stop() will signal the worker to exit and join the thread. The worker will
 *   flush any remaining messages before exiting.
 * - log() is thread-safe for multiple producers. If the ring buffer is full,
 *   log() prints an error to std::cerr and drops the message.
 *
 * Threading model:
 * - Multiple threads (producers) call `log()` concurrently.
 * - A single background thread (consumer) runs `process()` and writes to file.
 *
 * Example:
 * @code
 * kyra::LoggerDescriptor desc;
 * desc.file = "app.log";
 * desc.append = true;
 * desc.bufferSize = 4096;
 *
 * kyra::Logger::get().start(desc);
 * KYRA_LOG_INFO("App started, version " << version);
 * kyra::Logger::get().stop();
 * @endcode
 */

#include <KyraGameEngine/Container/RingBufferMPSC.hpp>
#include "LogMessage.hpp"
#include <thread>
#include <atomic>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <condition_variable> // required for std::condition_variable

namespace kyra {

	/**
  * @struct LoggerDescriptor
  * @brief Configuration parameters used when starting the logger.
  *
  * Fields:
  * - `file` : output file path. Defaults to "KyraGameEngine.log.txt".
  * - `append` : when true, open the file in append mode; otherwise overwrite.
  * - `bufferSize` : capacity of the internal ring buffer (number of messages).
  *
  * The `bufferSize` should be chosen according to expected message throughput
  * and memory constraints. A larger value reduces the chance of dropped messages.
  */
	struct LoggerDescriptor {
		std::string file = "KyraGameEngine.log.txt";
		bool append = false;
		size_t bufferSize = 1024;
	};

	/**
  * @class Logger
  * @brief Singleton asynchronous logger.
  *
  * Responsibilities:
  * - Accept log messages from multiple producers via `log()`.
  * - Buffer messages in a `RingBufferMPSC<LogMessage>` (multi-producer, single-consumer).
  * - Run a dedicated worker thread that flushes messages to a file.
  *
  * Lifetime and usage:
  * - Use `Logger::get()` to obtain the singleton instance.
  * - Call `start()` once at application initialization to configure and start the worker.
  * - Call `stop()` during shutdown to flush remaining logs and join the worker.
  *
  * Thread-safety:
  * - `start()`, `stop()`, and `log()` are safe to call from multiple threads
  *   with the caveat that `start()` should logically be called before intensive logging.
  */
	class Logger {

		// Internal ring buffer used to pass messages from producers to the consumer.
		RingBufferMPSC<LogMessage> m_RingBuffer;

		// Worker thread that consumes messages and writes them to disk.
		std::thread m_Worker;

		// Flag that indicates whether the worker should be running.
		std::atomic<bool> m_IsRunning = false;

		// Mutex/condition pair used only to notify the worker thread when new data arrives
		// or when the logger is requested to stop. The mutex is not used to protect the
		// ring buffer (it is lock-free), but to provide a blocking wait for the worker.
		std::mutex m_Mutex;
		std::condition_variable m_Condition;

		/**
   * @brief Worker loop that writes buffered messages to `fileName`.
   *
   * @param fileName Path of the file to open for writing.
   * @param append If true, open the file in append mode; otherwise overwrite.
   *
   * Behavior:
   * - Opens the file with appropriate flags.
   * - Continuously waits for either new messages or the stop signal.
   * - When woken, drains as many messages as possible from the ring buffer
   *   WITHOUT holding `m_Mutex`, writing them to the file.
   * - Continues until `m_IsRunning` is false and the ring buffer is empty.
   *
   * Exception handling:
   * - Any std::exception thrown during processing is caught and reported
   *   to `std::cerr`. The worker then exits.
   *
   * Note: `m_Condition.wait` uses a predicate to avoid spurious wakeups.
   */
		void process(const std::string& fileName, bool append);
	
	/**
   * @brief Convert `LogLevel` enum to a textual representation.
   *
   * @param level The LogLevel value to convert.
   * @return A constant C-string representing the level.
   *
   * This function is constexpr and returns a stable pointer to a static string
   * literal; callers must not attempt to free or modify the returned pointer.
   */
		constexpr const char* toString(LogLevel level) const {
			switch (level) {
			case LogLevel::Trace: return "TRACE";
			case LogLevel::Debug: return "DEBUG";
			case LogLevel::Info: return "INFO";
			case LogLevel::Warn: return "WARN";
			case LogLevel::Error: return "ERROR";
			case LogLevel::Fatal: return "FATAL";
			}
			return "UNKNOWN";
		}

	public:
	
   /**
   * @brief Destructor ensures the logger is stopped.
   *
   * If `start()` was called and the logger is still running when the destructor
   * is invoked, `stop()` will be called to ensure the worker thread is joined.
   */
		~Logger();

		/**
   * @brief Obtain the singleton instance of the logger.
   *
   * @return Reference to the global `Logger` instance.
   *
   * The instance is created on first use (thread-safe since C++11).
   */
		static Logger& get();

		/**
   * @brief Start the logger with the given configuration descriptor.
   *
   * @param descriptor The `LoggerDescriptor` that configures file path, append mode, and buffer size.
   *
   * Behavior:
   * - If the logger is not already running, initializes the ring buffer and
   *   spawns the worker thread that runs `process()`.
   * - If the logger is already running, this call is a no-op.
   *
   * Thread-safety:
   * - Safe to call concurrently; only the first successful caller will start the logger.
   */
		void start(LoggerDescriptor descriptor);

		/**
   * @brief Stop the logger and join the worker thread.
   *
   * Behavior:
   * - Sets the running flag to false and notifies the worker to wake up.
   * - Worker will flush remaining messages and exit; this method joins the thread.
   *
   * Thread-safety:
   * - Safe to call from any thread. Calling `stop()` multiple times is safe.
   */
		void stop();

		/**
   * @brief Push a formatted log message to the internal buffer.
   *
   * @param level Severity level of the message.
   * @param text Human-readable message text (copied).
   * @param frame Optional frame number associated with the message (default 0).
   *
   * Behavior:
   * - Constructs a `LogMessage` containing the caller thread id and the provided text.
   * - Attempts to push into the ring buffer. If successful, notifies the worker.
   * - If the ring buffer is full, prints an error to `std::cerr` and drops the message.
   *
   * Thread-safety:
   * - Safe to call concurrently from multiple producer threads.
   */
		void log(LogLevel level, std::string text, uint64_t frame = 0);

	};

} // namespace kyra

/**
 * Convenience macros for streaming-style logging.
 *
 * Each macro constructs a temporary `std::ostringstream`, streams the provided
 * arguments into it (using `operator<<`), and forwards the resulting string to
 * `kyra::Logger::get().log()` with the corresponding `LogLevel`.
 *
 * Usage:
 *   KYRA_LOG_INFO("Value: " << value << ", state: " << state);
 *
 * Notes:
 * - Because a temporary string is created, avoid extremely frequent use in tight loops
 *   if performance is critical. Use this convenience for readability.
 * - The macros expand to a `do { ... } while(0)` construct to be safe in all contexts.
 */
#define KYRA_LOG_TRACE(...) do { std::ostringstream _kyra_log_oss; _kyra_log_oss << __VA_ARGS__; kyra::Logger::get().log(kyra::LogLevel::Trace, _kyra_log_oss.str()); } while(0)
#define KYRA_LOG_DEBUG(...) do { std::ostringstream _kyra_log_oss; _kyra_log_oss << __VA_ARGS__; kyra::Logger::get().log(kyra::LogLevel::Debug, _kyra_log_oss.str()); } while(0)
#define KYRA_LOG_INFO(...)  do { std::ostringstream _kyra_log_oss; _kyra_log_oss << __VA_ARGS__; kyra::Logger::get().log(kyra::LogLevel::Info,  _kyra_log_oss.str()); } while(0)
#define KYRA_LOG_WARN(...)  do { std::ostringstream _kyra_log_oss; _kyra_log_oss << __VA_ARGS__; kyra::Logger::get().log(kyra::LogLevel::Warn,  _kyra_log_oss.str()); } while(0)
#define KYRA_LOG_ERROR(...) do { std::ostringstream _kyra_log_oss; _kyra_log_oss << __VA_ARGS__; kyra::Logger::get().log(kyra::LogLevel::Error, _kyra_log_oss.str()); } while(0)
#define KYRA_LOG_FATAL(...) do { std::ostringstream _kyra_log_oss; _kyra_log_oss << __VA_ARGS__; kyra::Logger::get().log(kyra::LogLevel::Fatal, _kyra_log_oss.str()); } while(0)
	
#endif