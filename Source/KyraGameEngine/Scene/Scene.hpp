#ifndef KYRAGAMEENGINE_SCENE_SCENE_HPP
#define KYRAGAMEENGINE_SCENE_SCENE_HPP

#include <vector>
#include <KyraGameEngine/Graphics/Sprite.hpp>

namespace kyra {
	class Scene {
		
		std::vector<Sprite*> m_Sprites;
		
		public:
		
		const std::vector<Sprite*>& getSprites() const {
			return m_Sprites;
		}
		
		
		void addSprite(Sprite* sprite) {
			m_Sprites.push_back(sprite);
		}
	};
	
}

#endif