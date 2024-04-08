#ifndef KYRAGAMEENGINE_LOG_LOGSTREAMFILE_HPP
#define KYRAGAMEENGINE_LOG_LOGSTREAMFILE_HPP

#include "ILogStream.hpp"
#include <fstream>
#include <string>

namespace kyra {
	
	// ILogStream implementation used for logging to a file
	class LogStreamFile : public ILogStream {
		
		std::ofstream m_Stream;
		
		public:
		LogStreamFile(std::string_view file);
		
		~LogStreamFile();
		
		virtual std::ostream& getStream();
		
	};
}

#endif