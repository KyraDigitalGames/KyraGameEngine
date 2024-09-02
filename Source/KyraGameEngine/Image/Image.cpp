#include "Image.hpp"

/// \todo Replace stb_image
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/// \todo Replace stb_image_write
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/// \todo Remove this
#include <iostream>

namespace kyra {
	
	Image::~Image() {
		free();
	}
	
	void Image::free() {
		if(m_Buffer) {
			if(m_SelfAllocated) {
				delete[] m_Buffer;
			} else {
				stbi_image_free(m_Buffer);
			}
			m_Buffer = nullptr;
		}
		m_Width = 0;
		m_Height = 0;
		m_Channels = 0;
	}
	
	bool Image::load(const std::string_view file) {
		free();
		m_Buffer = stbi_load(file.data(), &m_Width, &m_Height, &m_Channels, 0);
		return (m_Buffer != nullptr);
	}
	
	bool Image::create(int32_t width, int32_t height, int32_t channels) {
		free();
		m_Buffer = new uint8_t[width*height*channels]; 
		m_Width = width;
		m_Height = height;
		m_Channels = channels;
		m_SelfAllocated = true;
		return true;
	}
	
	bool Image::save(const std::string_view file, bool writeBMP) {
		if(writeBMP) {
			return stbi_write_bmp(file.data(), m_Width, m_Height, m_Channels, m_Buffer);			
		} else {
			return stbi_write_png(file.data(), m_Width, m_Height, m_Channels, m_Buffer, m_Width*m_Channels);
		}
	}

}