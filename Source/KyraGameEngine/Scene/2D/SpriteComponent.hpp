#ifndef KYRAGAMEENGINE_SCENE_2D_SPRITECOMPONENT_HPP
#define KYRAGAMEENGINE_SCENE_2D_SPRITECOMPONENT_HPP

#include <KyraGameEngine/Asset/Asset.hpp>
#include <KyraGameEngine/Scene/Component.hpp>
#include <memory>

#include "TransformComponent2D.hpp"

namespace kyra {
	
	class SpriteComponent : public kyra::Component {

		TextureAsset::Handle m_Texture;

	public:

		const kyra::Matrix4& getTransform() const {
			return getNode()->getComponent<kyra::TransformComponent2D>()->getTransform();
		}

		virtual std::size_t getHash() const {
			return typeid(SpriteComponent).hash_code();
		}

		const TextureAsset::Handle& getTexture() const {
			return m_Texture;
		}

		void setTexture(TextureAsset::Handle& texture) {
			m_Texture = texture;
		}

	};

}

#endif