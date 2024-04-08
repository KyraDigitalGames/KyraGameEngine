#ifndef KYRAGAMENGINE_LOG_LOGGER_HPP
#define KYRAGAMENGINE_LOG_LOGGER_HPP

#include <memory>
#include "LogStreamConsole.hpp"

namespace kyra {
		
	class Logger {

		// The used LogStream interface - Default is LogStreamConsole
		std::unique_ptr<ILogStream> m_Stream;
		
		public:
		Logger();
		
		// Return the singleton instance of the logger
		static Logger& getInstance();
		
		// Return the stream we are logging to
		std::ostream& log();
		
	};
	
}

#define KYRA_LOG_INFO(sender, message) kyra::Logger::getInstance().log() << "[INFO] - " << #sender << " - " << message << std::endl;
#define KYRA_LOG_ERROR(sender, message) kyra::Logger::getInstance().log() << "[ERROR] - " << #sender << " - " << message << std::endl;
#define KYRA_LOG_DEBUG(sender, message) kyra::Logger::getInstance().log() << "[DEBUG] - " << #sender << " - " << message << std::endl;
#define KYRA_LOG_WARNING(sender, message) kyra::Logger::getInstance().log() << "[WARNING] - " << #sender << " - " << message << std::endl;

#endif