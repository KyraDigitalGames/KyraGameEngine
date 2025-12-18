#ifndef KYRAGAMEENGINE_IMAGE_IMAGE_HPP
#define KYRAGAMEENGINE_IMAGE_IMAGE_HPP

#include <vector>
#include <string>

namespace kyra {

	class Image {
		
		std::vector<unsigned char> m_Data;
		int m_Width = 0;
		int m_Height = 0;
		int m_Channels = 0;
		std::string m_Path = "";

	public:

		bool load(const std::string& file);
		const unsigned char* getData() const;
		int getWidth() const;
		int getHeight() const;
		int getChannels() const;
		const std::string& getPath() const;
	};


}


#endif

