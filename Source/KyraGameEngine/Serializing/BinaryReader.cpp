#include "BinaryReader.hpp"

namespace kyra {
  
  template<>
	void BinaryReader::read(std::string& value) {
		std::size_t length = 0;
		read(length);
		value.resize(length);
		m_Stream.read(&value[0], length);
	}
  
}