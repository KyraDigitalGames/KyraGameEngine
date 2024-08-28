#ifndef KYRAGAMEENGINE_MATH_VECTOR2_HPP
#define KYRAGAMEENGINE_MATH_VECTOR2_HPP

#include <cstdint>

namespace kyra {

template<class T>
	class Vector2 {
		
		T m_Data[2];
		
		public:
		constexpr Vector2() : m_Data{0,0} {
			
		}
		
		constexpr Vector2(T v1, T v2) : m_Data{v1,v2} {
			
		}
		
		T& operator[] (std::size_t index) {
			return m_Data[index];
		}
		
		constexpr T operator[] (std::size_t index) const {
			return m_Data[index];
		}
		
	};
}

#endif