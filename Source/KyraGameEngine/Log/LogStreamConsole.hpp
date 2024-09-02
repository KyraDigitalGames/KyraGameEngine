#ifndef KYRAGAMEENGINE_LOG_LOGSTREAMCONSOLE_HPP
#define KYRAGAMEENGINE_LOG_LOGSTREAMCONSOLE_HPP

#include <iostream>

namespace kyra {
	
	class LogStreamConsole : public AbstractLogStream {
		
		public:
		
		std::ostream& get() final {
			return std::cout;
		}
		
	};
	
}

#endif