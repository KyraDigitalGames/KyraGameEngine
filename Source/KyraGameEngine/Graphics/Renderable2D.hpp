#ifndef KYRAGAMEENGINE_GRAPHICS_RENDERABLE2D_HPP
#define KYRAGAMEENGINE_GRAPHICS_RENDERABLE2D_HPP

namespace kyra {
	
	class Renderable2D {
		
		public:
		virtual ~Renderable2D() = default;
		
		virtual constexpr std::size_t getElementCount() const = 0;
		virtual constexpr std::size_t getSize() const = 0;
		virtual constexpr const void* getDataPtr() const = 0;
		
	};
	
}

#endif