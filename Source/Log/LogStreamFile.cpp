
#include <KyraGameEngine/Log/LogStreamFile.hpp>

namespace kyra {

	LogStreamFile::LogStreamFile(std::string_view file) {
		m_Stream.open(file.data());
	}
		
	LogStreamFile::~LogStreamFile() {
		m_Stream.close();
	}
		
	std::ostream& LogStreamFile::getStream() {
		return m_Stream;
	}
		
}
