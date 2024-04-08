#ifndef KYRAGAMEENGINE_LOG_ILOGSTREAM_HPP
#define KYRAGAMEENGINE_LOG_ILOGSTREAM_HPP

#include <ostream>

namespace kyra {
	
	// Interface class for LogStream implementations
	class ILogStream {
		
		public:
		virtual ~ILogStream() = default;
		
		// Return a reference to the stream we are logging to
		virtual std::ostream& getStream() = 0;
		
	};
}

#endif