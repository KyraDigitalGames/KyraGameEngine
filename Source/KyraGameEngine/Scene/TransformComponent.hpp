#ifndef KYRAGAMEENGINE_SCENE_TRANSFORMCOMPONENT_HPP
#define KYRAGAMEENGINE_SCENE_TRANSFORMCOMPONENT_HPP

#include <KyraGameEngine/Math/Vector3.hpp>
#include <KyraGameEngine/Math/Matrix4.hpp>

#include "Component.hpp"

namespace kyra {
    
class TransformComponent : public Component {

	kyra::Vector3<float> m_Position;
	kyra::Vector3<float> m_Size;

	mutable kyra::Matrix4 m_LocalTransform;
	mutable bool m_IsLocalTransformDirty = true;

	mutable kyra::Matrix4 m_WorldTransform;
	mutable bool m_IsWorldTransformDirty = true;


	public:

	void markWorldDirty() {
		m_IsWorldTransformDirty = true;
		for (auto* c : getNode()->getChildren()) {
			if (c->hasComponent<TransformComponent>()) {
				c->getComponent<TransformComponent>()->markWorldDirty();
			}
		}
	}

	void setPosition(const kyra::Vector3<float>& position) {
		m_Position = position;
		m_IsLocalTransformDirty = true;
	}

	const kyra::Vector3<float>& getPosition() const {
		return m_Position;
	}

	void setSize(const kyra::Vector3<float>& size) {
		m_Size = size;
		m_IsLocalTransformDirty = true;
	}

	const kyra::Vector3<float>& getSize() const {
		return m_Size;
	}

	const kyra::Matrix4& getTransform() const {
		if (m_IsLocalTransformDirty) {
			m_LocalTransform = kyra::Matrix4()
				.scale(m_Size)
				.translate(m_Position);
			m_IsLocalTransformDirty = false;
			m_IsWorldTransformDirty = true;
		}
		if (m_IsWorldTransformDirty) {
			const Node* parentNode = getNode()->getParent();
			if (parentNode) {
				if (parentNode->hasComponent<TransformComponent>()) {
					const TransformComponent* parentTransform = parentNode->getComponent<TransformComponent>();
					m_WorldTransform = parentTransform->getTransform() * m_LocalTransform;
				}
				else {
					m_WorldTransform = m_LocalTransform;
				}
			}
			else {
				m_WorldTransform = m_LocalTransform;
			}
			m_IsWorldTransformDirty = false;
		}
		return m_WorldTransform;
	}

	virtual std::size_t getHash() const {
		return typeid(TransformComponent).hash_code();
	}

};
  
}

#endif