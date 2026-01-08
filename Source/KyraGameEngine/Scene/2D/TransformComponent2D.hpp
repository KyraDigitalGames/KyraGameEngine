#ifndef KYRAGAMEENGINE_SCENE_2D_TRANSFORMCOMPONENT2D_HPP
#define KYRAGAMEENGINE_SCENE_2D_TRANSFORMCOMPONENT2D_HPP

#include <KyraGameEngine/Math/Vector2.hpp>
#include <KyraGameEngine/Math/Matrix4.hpp>
#include <KyraGameEngine/Scene/Component.hpp>
#include <KyraGameEngine/SCene/Node.hpp>


namespace kyra {

	class TransformComponent2D : public Component {

		kyra::Vector2<float> m_Position = { 0,0 };
		kyra::Vector2<float> m_Size = { 1,1 };

		mutable kyra::Matrix4 m_LocalTransform;
		mutable bool m_IsLocalTransformDirty = true;

		mutable kyra::Matrix4 m_WorldTransform;
		mutable bool m_IsWorldTransformDirty = true;


	public:

		void markWorldDirty() {
			m_IsWorldTransformDirty = true;
			for (auto* c : getNode()->getChildren()) {
				if (c->hasComponent<TransformComponent2D>()) {
					c->getComponent<TransformComponent2D>()->markWorldDirty();
				}
			}
		}

		void setPosition(const kyra::Vector2<float>& position) {
			m_Position = position;
			m_IsLocalTransformDirty = true;
		}

		const kyra::Vector2<float>& getPosition() const {
			return m_Position;
		}

		void setSize(const kyra::Vector2<float>& size) {
			m_Size = size;
			m_IsLocalTransformDirty = true;
		}

		const kyra::Vector2<float>& getSize() const {
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
					if (parentNode->hasComponent<TransformComponent2D>()) {
						const TransformComponent2D* parentTransform = parentNode->getComponent<TransformComponent2D>();
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
			return typeid(TransformComponent2D).hash_code();
		}

	};

}

#endif