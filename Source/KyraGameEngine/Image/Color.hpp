#ifndef KYRAGAMEENGINE_IMAGE_COLOR_HPP
#define KYRAGAMEENGINE_IMAGE_COLOR_HPP

#include <cstdint>
#include <array>
#include <iostream>

namespace kyra {
	
	class Color {
		
		float m_Data[4];
		
		public:
		constexpr Color( uint8_t r, uint8_t g, uint8_t b, uint8_t a) : m_Data{ static_cast<float>(r) / 255.f,
																			   static_cast<float>(g) / 255.f,
																			   static_cast<float>(b) / 255.f,
																			   static_cast<float>(a) / 255.f}
		{
			
		}

		constexpr Color( uint8_t r, uint8_t g, uint8_t b) : m_Data{ static_cast<float>(r) / 255.f,
																			   static_cast<float>(g) / 255.f,
																			   static_cast<float>(b) / 255.f,
																			   1.0f}
		{
			
		}

		
		constexpr Color( float r, float g, float b, float a) : m_Data{r,g,b,a} {
			
		}
		
		constexpr std::array<uint8_t, 4> toUINT8() const {
			return {	static_cast<uint8_t>(m_Data[0] * 255.f), 
						static_cast<uint8_t>(m_Data[1] * 255.f), 
						static_cast<uint8_t>(m_Data[2] * 255.f), 
						static_cast<uint8_t>(m_Data[3] * 255.f)};
		}
		
		constexpr uint32_t toUINT32() const {
			auto val = toUINT8();
			return ( static_cast<uint32_t>(val[0]) << 24 ) |
				   ( static_cast<uint32_t>(val[1]) << 16 ) |
				   ( static_cast<uint32_t>(val[2]) << 8 ) |
				   ( static_cast<uint32_t>(val[3]) );
		}
		
		constexpr float getR() const {
			return m_Data[0];
		}
		
		constexpr float getG() const {
			return m_Data[1];
		}
		
		constexpr float getB() const {
			return m_Data[2];
		}
		
		constexpr float getA() const {
			return m_Data[3];
		}
		
		constexpr bool operator == (const Color& color) const {
			return m_Data[0] == color.m_Data[0] &&
				   m_Data[1] == color.m_Data[1] &&
				   m_Data[2] == color.m_Data[2] &&
				   m_Data[3] == color.m_Data[3];
		}
				
	};
	
}

#endif