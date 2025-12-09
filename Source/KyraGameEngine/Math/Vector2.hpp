#ifndef KYRAGAMEENGINE_MATH_VECTOR2_HPP
#define KYRAGAMEENGINE_MATH_VECTOR2_HPP

namespace kyra {
	
	template<class T>
	class Vector2 {
		
		T m_Data[2];
		
		public:
		constexpr Vector2() noexcept : m_Data{0,0} {
		
		}
		
		constexpr Vector2(T x, T y) noexcept : m_Data{x,y} {
		
		}
		
		constexpr T getX() const {
			return m_Data[0];
		}
		
		constexpr T getY() const {
			return m_Data[1];
		}
		
	};
	
}

#endif