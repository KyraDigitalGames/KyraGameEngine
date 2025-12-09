#ifndef KYRAGAMEENGINE_MATH_VECTOR4_HPP
#define KYRAGAMEENGINE_MATH_VECTOR4_HPP

namespace kyra {
	
	template<class T>
	class Vector4 {
		
		T m_Data[4];
		
		public:
		constexpr Vector4() noexcept : m_Data{0,0,0,0} {
		
		}
		
		constexpr Vector4(T x, T y, T z, T w) noexcept : m_Data{x,y,z,w} {
		
		}
		
		constexpr T getX() const {
			return m_Data[0];
		}
		
		constexpr T getY() const {
			return m_Data[1];
		}
		
		constexpr T getZ() const {
			return m_Data[2];
		}
		
		constexpr T getW() const {
			return m_Data[3];
		}
		
	};
	
}

#endif