#ifndef KYRAGAMEENGINE_RENDERER_RENDERPIPELINE_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPIPELINE_HPP

#include "RenderPass.hpp"
#include "CommandBuffer.hpp"
#include <vector>
#include <memory>
#include <KyraGameEngine/GameModule/GameModule.hpp>
#include <KyraGameEngine/Serializing/Serializable.hpp>
#include <string>

#include <KyraGameEngine/Renderer/Swapchain.hpp>

namespace kyra {

	
	struct RenderPassEntry : public Serializable {
		std::string name;
		std::string processorName;

		void write(BinaryWriter& writer) override {
			writer.write(name);
			writer.write(processorName);
		}

		void read(BinaryReader& reader) override {
			reader.read(name);
			reader.read(processorName);
		}

	};

	struct RenderPipelineDescriptor : public Serializable {
	
		Renderer* renderer = nullptr;
		SystemManager* systemManager = nullptr;
		Registry<RenderPass>* renderPassRegistry = nullptr;
		Registry<RenderPassProcessor>* renderPassProcessorRegistry = nullptr;
		std::vector<RenderPassEntry> m_RenderPasses;
	
		void write(BinaryWriter& writer) override {
			std::size_t count = m_RenderPasses.size();
			writer.write(count);
			for (auto& entry : m_RenderPasses) {
				entry.write(writer);
			}
		}

		void read(BinaryReader& reader) override {
			std::size_t count = 0;
			reader.read(count);
			m_RenderPasses.resize(count);
			for (std::size_t i = 0; i < count; ++i) {
				m_RenderPasses[i].read(reader);
			}
		}	
	
	};

	class RenderPipeline {

		CommandBuffer* m_CommandBuffer = nullptr;
		Swapchain* m_Swapchain = nullptr;
		Renderer* m_Renderer = nullptr;
		SystemManager* m_SystemManager = nullptr;
		std::vector<std::shared_ptr<RenderPass>> m_RenderPasses;

	public:

		bool init(RenderPipelineDescriptor& descriptor);
		

		void renderFrame();

	};

}

#endif