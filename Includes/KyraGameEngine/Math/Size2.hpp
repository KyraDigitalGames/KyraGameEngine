#ifndef KYRAGAMEENGINE_MATH_SIZE2_HPP
#define KYRAGAMEENGINE_MATH_SIZE2_HPP

namespace kyra {
	
	template<class T>
	class Size2 {
		
		T m_Data[2];
		
		public:
		constexpr Size2() : m_Data{0,0} {
			
		}
		
		constexpr Size2(T width, T height) : m_Data{width, height} {
			
		}
		
		constexpr T getWidth() const {
			return m_Data[0];
		}
		
		constexpr T getHeight() const {
			return m_Data[1];
		}
		
	};
}

#endif