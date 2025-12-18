#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace kyra {

	bool Image::load(const std::string& file) {
		m_Path = file;
		unsigned char* data = stbi_load(file.c_str(), &m_Width, &m_Height, &m_Channels, 0);
		if (!data) {
			return false;
		}
		m_Data.resize(m_Width * m_Height * m_Channels);
		memcpy(&m_Data[0], data, m_Width * m_Height * m_Channels);
		stbi_image_free(data);
		return true;
	}

	const unsigned char* Image::getData() const {
		return m_Data.data();
	}

	int Image::getWidth() const {
		return m_Width;
	}

	int Image::getHeight() const {
		return m_Height;
	}

	int Image::getChannels() const {
		return m_Channels;
	}

	const std::string& Image::getPath() const {
		return m_Path;
	}



}