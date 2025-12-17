#ifndef KYRAGAMEENGINE_SERIALIZATION_BINARYWRITER_HPP
#define KYRAGAMEENGINE_SERIALIZATION_BINARYWRITER_HPP

#include <string>
#include <fstream>

namespace kyra {

	class BinaryWriter {

		std::ofstream m_Stream;

	public:
		~BinaryWriter() {
			if (m_Stream.is_open()) {
				m_Stream.close();
			}
		}

		bool open(const std::string& file) {
			m_Stream.open(file.c_str(), std::ios::binary);
			return m_Stream.is_open();
		}

		template<class T>
		void write(const T& value) {
			m_Stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
		}

		template<>
		void write(const std::string& value) {
			std::size_t length = value.length();
			write(length);
			m_Stream.write(value.c_str(), length);
		}

		void close() {
			m_Stream.close();
		}

	};

}

#endif