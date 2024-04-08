#ifndef KYRAGAMEENGINE_LOG_LOGSTREAMCONSOLE_HPP
#define KYRAGAMEENGINE_LOG_LOGSTREAMCONSOLE_HPP

#include "ILogStream.hpp"
#include <iostream>

namespace kyra {
	
	// ILogStream implementation used for logging to the console
	class LogStreamConsole : public ILogStream {
		
		public:

		virtual std::ostream& getStream();
		
	};
}

#endif