#ifndef KYRAGAMEENGINE_MATH_VECTOR4_HPP
#define KYRAGAMEENGINE_MATH_VECTOR4_HPP

namespace kyra {
	template<class T>
	class Vector4 {
		
		T m_Data[4];
		
		public:
		constexpr Vector4() : m_Data{0,0,0,0} {
			
		}
		
		constexpr Vector4(T v1, T v2, T v3, T v4) : m_Data{v1,v2,v3,v4} {
			
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