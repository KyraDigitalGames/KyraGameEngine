#ifndef KYRAGAMEENGINE_SCENE_2D_SCENESYSTEM2D_HPP
#define KYRAGAMEENGINE_SCENE_2D_SCENESYSTEM2D_HPP

#include "SpriteComponent.hpp"
#include "TransformComponent2D.hpp"
#include <KyraGameEngine/Core/System.hpp>
#include <memory>
#include <vector>
#include <KyraGameEngine/Scene/Scene.hpp>

namespace kyra {

	class MeshComponent2D : public Component {

		std::vector<float> m_Vertices;

	public:

		std::size_t getDataSize() const {
			return m_Vertices.size() * sizeof(float);
		}

		void* getData() {
			return reinterpret_cast<void*>(&m_Vertices[0]);
		}

		void setData(const std::vector<float>& vertices) {
			m_Vertices = vertices;
		}

		const Matrix4& getTransform() const {
			return getNode()->getComponent<kyra::TransformComponent2D>()->getTransform();
		}

		virtual std::size_t getHash() const {
			return typeid(MeshComponent2D).hash_code();
		}

		std::size_t getVertexOffset() const {
			return 0;
		}

		std::size_t getVertexCount() const {
			return m_Vertices.size() / 4;
		}


	};

	class SceneSystem2D : public System {

		std::vector<std::unique_ptr<kyra::SpriteComponent>> m_SpriteComponents;
		std::vector<std::unique_ptr<kyra::TransformComponent2D>> m_TransformComponents;
		std::vector< std::unique_ptr<kyra::MeshComponent2D>> m_MeshComponents;

		std::map<std::string, std::unique_ptr<Scene>> m_Scenes;
		Scene* m_ActiveScene = nullptr;

	public:

		Scene* createScene(const std::string& name) {
			auto it = m_Scenes.find(name);
			if (it == m_Scenes.end()) {
				m_Scenes[name] = std::make_unique<Scene>();
				return m_Scenes[name].get();
			}
			return it->second.get();
		}

		Scene* getScene(const std::string& name) {
			auto it = m_Scenes.find(name);
			if (it == m_Scenes.end()) {
				return nullptr;
			}
			return it->second.get();
		}

		Scene* releaseScene(const std::string& name) {

		}

		void setActiveScene(Scene* scene) {
			m_ActiveScene = scene;
		}

		void setActiveScene(const std::string& name) {
			m_ActiveScene = m_Scenes[name].get();
		}

		SpriteComponent* createSpriteComponent() {
			m_SpriteComponents.emplace_back(std::make_unique<kyra::SpriteComponent>());
			return m_SpriteComponents.back().get();
		}

		MeshComponent2D* createMeshComponent() {
			m_MeshComponents.emplace_back(std::make_unique<kyra::MeshComponent2D>());
			return m_MeshComponents.back().get();
		}

		TransformComponent2D* createTransformComponent() {
			m_TransformComponents.emplace_back(std::make_unique<kyra::TransformComponent2D>());
			return m_TransformComponents.back().get();
		}

		std::vector<std::unique_ptr<MeshComponent2D>>& getMeshComponents() {
			return m_MeshComponents;
		}

		std::vector<std::unique_ptr<SpriteComponent>>& getSpriteComponents() {
			return m_SpriteComponents;
		}

		std::vector < std::unique_ptr<TransformComponent2D>>& getTransformComponents() {
			return m_TransformComponents;
		}

		void update(float deltaTime) {
			if (m_ActiveScene) {
				m_ActiveScene->renderFrame();
			}
		}

	};

}

#endif