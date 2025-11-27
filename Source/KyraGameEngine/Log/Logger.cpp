#include "Logger.hpp"

namespace kyra {

	Logger::~Logger() {
		if (m_IsRunning.load()) {
			stop();
		}
	}

	Logger& Logger::get() {
		static Logger instance;
		return instance;
	}
		
	void Logger::process(const std::string& fileName, bool append) {
		try {
			std::ios::openmode outputFlags = std::ios::out;
			if (append) {
				outputFlags |= std::ios::app;
			}
			std::ofstream file(fileName, outputFlags);
			// Keep running while logger is running or there are messages to flush
			while (m_IsRunning.load() || !m_RingBuffer.empty()) {
				// Wait until either stopped or there is data
				std::unique_lock<std::mutex> lock(m_Mutex);
				m_Condition.wait(lock, [&]() {
					return !m_IsRunning.load() || !m_RingBuffer.empty();
					});
				lock.unlock();

				// Drain available messages without holding the mutex
				LogMessage msg;
				while (m_RingBuffer.pop(msg)) {
					file << "[ " << toString(msg.level) << " ] - Frame " << msg.frame
						<< " - Thread " << msg.threadId << " : " << msg.text << "\n";
				}
			}
			file.close();
		}
		catch (std::exception& exception) {
			std::cerr << "[LOGGER] Logger::process exception: " << exception.what() << std::endl;
		}
	}

	void Logger::start(LoggerDescriptor descriptor) {
		bool value = false;
		if (m_IsRunning.compare_exchange_strong(value, true)) {
			m_RingBuffer.init(descriptor.bufferSize);
			m_Worker = std::thread([this, descriptor]() {
				this->process(descriptor.file, descriptor.append);
				});
		}
	}

	void Logger::stop() {
		m_IsRunning = false;
		m_Condition.notify_one(); // wake worker so wait() unblocks
		if (m_Worker.joinable()) m_Worker.join();
	}

	void Logger::log(LogLevel level, std::string text, uint64_t frame) {
		LogMessage msg{ level, text, frame, std::this_thread::get_id() };
		if (m_RingBuffer.push(msg)) {
			// wake the worker (single consumer)
			m_Condition.notify_one();
		}
		else {
			std::cerr << "[LOGGER] Buffer overflow, message dropped: " << text << std::endl;
		}
	}



}