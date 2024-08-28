#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace kyra {
	
	bool Image::load(const std::string_view file) {
		m_Buffer = stbi_load(file.data(), &m_Width, &m_Height, &m_Channels, 0);
		return (m_Buffer != nullptr);
	}

}