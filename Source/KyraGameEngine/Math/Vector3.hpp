#ifndef KYRAGAMEENGINE_MATH_VECTOR3_HPP
#define KYRAGAMEENGINE_MATH_VECTOR3_HPP

#include <cstdint>

namespace kyra {

template<class T>
	class Vector3 {
		
		T m_Data[3];
		
		public:
		constexpr Vector3() : m_Data{0,0,0} {
			
		}
		
		constexpr Vector3(T v1, T v2, T v3) : m_Data{v1,v2, v3} {
			
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