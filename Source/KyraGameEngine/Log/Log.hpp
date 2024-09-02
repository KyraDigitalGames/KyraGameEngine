#ifndef KYRAGAMEENGINE_LOG_LOG_HPP
#define KYRAGAMEENGINE_LOG_LOG_HPP

#include "AbstractLogStream.hpp"
#include "LogStreamConsole.hpp"
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

namespace kyra {
	
	class Log {

		std::unique_ptr<AbstractLogStream> m_Stream;
		std::vector<std::string> m_Content;
		std::thread m_Thread;
		std::mutex m_Mutex;
		bool m_ShouldStop = false;
		bool m_IsRunning = false;

		static Log& getInstance() {
			static Log instance;
			return instance;
		}
		
		
		public:
		Log() {
			m_Stream = std::make_unique<LogStreamConsole>();
			m_IsRunning = true;
			m_Thread = std::thread([&](){
				while(!m_ShouldStop) {
					std::this_thread::sleep_for(25ms);
					std::scoped_lock lock(m_Mutex);
					for(auto& entry : m_Content) {
						m_Stream->get() << entry << std::endl;
					}
					m_Content.clear();
				}
				std::scoped_lock lock(m_Mutex);
				for(auto& entry : m_Content) {
					m_Stream->get() << entry;
				}
				m_Content.clear();
				m_IsRunning = false;
			});
		}
		
		~Log() {
			m_ShouldStop = true;
			if(m_Thread.joinable()) {
				m_Thread.join();
			}
		}
		
		static void info(const std::string& message) {
			std::scoped_lock lock(getInstance().m_Mutex);
			getInstance().m_Content.push_back(message);
		}
		
		static void error(const std::string& message) {
			std::scoped_lock lock(getInstance().m_Mutex);
			getInstance().m_Content.push_back(message);
		}
		
		static void warning(const std::string& message) {
			std::scoped_lock lock(getInstance().m_Mutex);		
			getInstance().m_Content.push_back(message);
		}
		
		static void join() {
			getInstance().m_ShouldStop = true;
			if(getInstance().m_Thread.joinable()) {
				getInstance().m_Thread.join();
			}
			while(getInstance().m_IsRunning) {
				// Wait for finish
			}
		}
				
	};
	
}

#endif