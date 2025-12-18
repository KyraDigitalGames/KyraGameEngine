#ifndef KYRAGAMEENGINE_SCENE_HPP
#define KYRAGAMEENGINE_SCENE_HPP

#include <string>
#include <memory>

#include "Node.hpp"

namespace kyra {

	class Scene  {

		std::map<std::string, std::unique_ptr<kyra::Node>> m_Nodes;
		kyra::RenderPipeline* m_RenderPipeline;

	public:
		
		kyra::Node* createNode(const std::string& id) {
			auto it = m_Nodes.emplace(id, std::make_unique<kyra::Node>());
			if(!it.second) {
				return nullptr;
			}
		    it.first->second->setName(id);
			it.first->second->setScene(this);
     		return it.first->second.get();
		}

		kyra::Node* getNode(const std::string& id) {
			auto it = m_Nodes.find(id);
			if (it == m_Nodes.end()) {
				return nullptr;
			}
			return it->second.get();
		}

		void setRenderPipeline(kyra::RenderPipeline* renderPipeline) {
			m_RenderPipeline = renderPipeline;
		}

		void renderFrame() {
			if (m_RenderPipeline) {
				m_RenderPipeline->renderFrame();
			}
		}

		void write(BinaryWriter& binaryWriter) {
		
		}

	};

}

#endif