
#include <KyraGameEngine/Log/Logger.hpp>

namespace kyra {
		
	Logger::Logger() {
		m_Stream = std::make_unique<LogStreamConsole>();
	}
		
	Logger& Logger::getInstance() {
		static Logger instance;
		return instance;
	}
		
	std::ostream& Logger::log() {
		return m_Stream->getStream();
	} 
	
}