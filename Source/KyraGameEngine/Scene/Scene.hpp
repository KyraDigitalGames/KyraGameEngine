#ifndef KYRAGAMEENGINE_SCENE_HPP
#define KYRAGAMEENGINE_SCENE_HPP

#include <KyraGameEngine/Core/SystemManager.hpp>
#include <string>
#include <memory>

namespace kyra {

	class Scene : public kyra::System {

		std::map<std::string, std::unique_ptr<kyra::Node>> m_Nodes;
		kyra::RenderPipeline m_RenderPipeline;

	public:
		
		kyra::Node* createNode(const std::string& id) {
			auto it = m_Nodes.emplace(id, std::make_unique<kyra::Node>());
			return (it.second) ? it.first->second.get() : nullptr;
		}

		kyra::Node* getNode(const std::string& id) {
			auto it = m_Nodes.find(id);
			if (it == m_Nodes.end()) {
				return nullptr;
			}
			return it->second.get();
		}

		void setRenderPipeline(kyra::RenderPipeline renderPipeline) {
			m_RenderPipeline = renderPipeline;
		}

		void update(float deltaTime) {
			m_RenderPipeline.renderFrame();
		}

		void write(BinaryWriter& binaryWriter) {
		
		}

	};

}

#endif