#ifndef KYRAGAMEENGINE_IMAGE_IMAGE_HPP
#define KYRAGAMEENGINE_IMAGE_IMAGE_HPP

#include <string_view>
#include <cstdint>

namespace kyra {
	
	class Image {
			
		uint8_t* m_Buffer = nullptr;
		int32_t m_Width = 0;
		int32_t m_Height = 0;
		int32_t m_Channels = 0;
	
		public:

		[[nodiscard]] bool load(const std::string_view file);
		
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