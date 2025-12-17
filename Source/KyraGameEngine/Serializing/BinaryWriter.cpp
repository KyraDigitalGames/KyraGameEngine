#include "BinaryWriter.hpp"

namespace kyra {
  
  template<>
	void BinaryWriter::write(const std::string& value) {
		std::size_t length = value.length();
		write(length);
		m_Stream.write(value.c_str(), length);
	}
  
}