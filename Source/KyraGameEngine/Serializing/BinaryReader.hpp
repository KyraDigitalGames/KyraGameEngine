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


		void close() {
			m_Stream.close();
		}

	};

		template<>
		void BinaryReader::read(std::string& value);


}

#endif