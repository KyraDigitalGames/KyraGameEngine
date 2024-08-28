#ifndef KYRAGAMEENGINE_GRAPHICS_SPRITE_HPP
#define KYRAGAMEENGINE_GRAPHICS_SPRITE_HPP

#include "Renderable2D.hpp"
#include <KyraGameEngine/Math/Vector2.hpp>
#include <KyraGameEngine/Math/Vector4.hpp>


namespace kyra {
	
	struct SpriteVertex {
		Vector2<float> position;
		Vector4<float> color;
		Vector2<float> uv;
	};
	
	class Sprite : public Renderable2D {
		
		SpriteVertex m_Vertices[6];
		
		public:
		Sprite() {
			m_Vertices[0].position = {1,1};
			m_Vertices[0].color    = {1,0,0,1};
			m_Vertices[1].position = {-1,-1};
			m_Vertices[1].color    = {0,1,0,1};
			m_Vertices[2].position = {-1,1};
			m_Vertices[2].color    = {0,0,1,1};
			m_Vertices[3].position = {1,1};
			m_Vertices[3].color    = {1,0,0,1};
			m_Vertices[4].position = {-1,-1};
			m_Vertices[4].color    = {0,1,0,1};
			m_Vertices[5].position = {1,-1};
			m_Vertices[5].color    = {0,0,1,1};
		}

		virtual constexpr std::size_t getSize() const {
			return 6 * sizeof(SpriteVertex);
		}
		
		virtual constexpr const void* getDataPtr() const {
			return &m_Vertices[0];
		}
				
		virtual constexpr std::size_t getElementCount() const {
			return 6;
		}
		
	};
	
}

#endif