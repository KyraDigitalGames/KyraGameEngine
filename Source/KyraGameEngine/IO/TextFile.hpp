#ifndef KYRAGAMEENGINE_IO_TEXTFILE_HPP
#define KYRAGAMEENGINE_IO_TEXTFILE_HPP

#include <fstream>
#include <string>
#include <filesystem>

namespace kyra {
	
	class TextFile {
		
		std::ifstream m_Stream;
		
		public:
		~TextFile() {
			m_Stream.close();
		}
		
		bool open(const std::filesystem::path& file) {
			m_Stream.open(file.c_str());
			return m_Stream.is_open();
		}
		
		std::string getContent() {
			std::string content;
			std::string line;
			while(!m_Stream.eof()) {
				std::getline(m_Stream, line);
				content += line + "\n";
			}
			return content;
		}
				
		void close() {
			m_Stream.close();
		}
		
	};
}

#endif