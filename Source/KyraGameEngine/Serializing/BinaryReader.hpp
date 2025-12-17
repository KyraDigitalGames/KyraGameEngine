#ifndef KYRAGAMEENGINE_SERIALIZATION_BINARYREADER_HPP
#define KYRAGAMEENGINE_SERIALIZATION_BINARYREADER_HPP

#include <string>
#include <fstream>

namespace kyra {

	class BinaryReader {

		std::ifstream m_Stream;

	public:
		~BinaryReader() {
			if (m_Stream.is_open()) {
				m_Stream.close();
			}
		}

		bool open(const std::string& file) {
			m_Stream.open(file.c_str(), std::ios::binary);
			return m_Stream.is_open();
		}

		template<class T>
		void read(T& value) {
			m_Stream.read(reinterpret_cast<char*>(&value), sizeof(T));
		}

		template<>
		void read(std::string& value) {
			std::size_t length = 0;
			read(length);
			value.resize(length);
			m_Stream.read(&value[0], length);
		}

		void close() {
			m_Stream.close();
		}

	};

}

#endif