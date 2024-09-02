#ifndef KYRAGAMEENGINE_LOG_ABSTRACTLOGSTREAM_HPP
#define KYRAGAMEENGINE_LOG_ABSTRACTLOGSTREAM_HPP

#include <ostream>

namespace kyra {
	
	class AbstractLogStream {
		
		public:
		virtual ~AbstractLogStream() = default;
		
		virtual std::ostream& get() = 0;
		
	};
	
}

#endif