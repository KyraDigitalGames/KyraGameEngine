#include "Profiling.hpp"
#include <unordered_map>
#include <string>


namespace kyra {

	std::unordered_map<std::string, FunctionEntry> Profiler::m_FunctionEntries;

}