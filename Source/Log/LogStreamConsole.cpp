
#include <KyraGameEngine/Log/LogStreamConsole.hpp>

namespace kyra {
	
	std::ostream& LogStreamConsole::getStream() {
		return std::cout;
	}
	
}
