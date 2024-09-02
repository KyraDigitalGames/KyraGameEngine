#ifndef KYRAGAMEENGINE_IMAGE_IMAGE_HPP
#define KYRAGAMEENGINE_IMAGE_IMAGE_HPP

#include "Color.hpp"

#include <string_view>
#include <cstdint>

namespace kyra {
	
	/// \todo Implement pixel access / color class
	class Image {
			
		uint8_t* m_Buffer = nullptr;
		int32_t m_Width = 0;
		int32_t m_Height = 0;
		int32_t m_Channels = 0;
		bool m_SelfAllocated = false;
	
		public:
		~Image();
		
		void free();

		[[nodiscard]] bool load(const std::string_view file);
		[[nodiscard]] bool create(int32_t width, int32_t height, int32_t channels);
		[[nodiscard]] bool save(const std::string_view file, bool writeBMP);
		
		constexpr Color getPixel(int32_t x, int32_t y) {
			uint8_t* index = &m_Buffer[(y*m_Width+x)*m_Channels];
			if(m_Channels == 3) {
				return Color(index[0], index[1], index[2]);
			}
			return Color(index[0], index[1], index[2], index[3]);
		}
		
		void setPixel(int32_t x, int32_t y, const Color& color) {
			auto colUINT8 = color.toUINT8();
			uint8_t* index = &m_Buffer[(y*m_Width+x)*m_Channels];
			index[0] = colUINT8[0];
			index[1] = colUINT8[1];
			index[2] = colUINT8[2];
			if(m_Channels == 4) {
				index[3] = colUINT8[3];
			}
		}
		
		constexpr uint8_t* getBuffer() const {
			return m_Buffer;
		} 
		
		constexpr uint32_t getWidth() const {
			return m_Width;
		}
		
		constexpr uint32_t getHeight() const {
			return m_Height;
		}
		
		constexpr uint32_t getChannels() const {
			return m_Channels;
		}
		
	};
}

#endif