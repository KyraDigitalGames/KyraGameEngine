#ifndef KYRAGAMEENGINE_MATH_VECTOR3_HPP
#define KYRAGAMEENGINE_MATH_VECTOR3_HPP

namespace kyra {
	
	template<class T>
	class Vector3 {
		
		T m_Data[3];
		
		public:
		constexpr Vector3() noexcept : m_Data{0,0,0} {
		
		}
		
		constexpr Vector3(T x, T y, T z) noexcept : m_Data{x,y, z} {
		
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
    
    Vector3<T>& operator += (const Vector3<T>& vec) {
      m_Data[0] += vec.m_Data[0];
      m_Data[1] += vec.m_Data[1];
      m_Data[2] += vec.m_Data[2];
      return *this;
    }
		
	};
	
}

#endif