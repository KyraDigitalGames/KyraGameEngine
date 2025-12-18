#ifndef KYRAGAMEENGINE_RENDERER_RENDERER_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERER_HPP

#include "RenderPipeline.hpp"
#include "RenderDeviceImplementation.hpp"
#include "VertexBuffer.hpp"
#include "RenderPipelineState.hpp"
#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Core/System.hpp>
#include <KyraGameEngine/Core/Registry.hpp>
#include <memory>


namespace kyra {

	enum class RenderDeviceType {
		OpenGL,
		Vulkan,
		Metal,
		DirectX11,
		DirectX12
	};

	struct RendererDescriptor {
		RenderDeviceType type = RenderDeviceType::OpenGL;
		Window* window = nullptr;
	};

	class Renderer : public System {

		std::unique_ptr<RenderDeviceImplementation> m_Implementation;
		RenderPipeline m_RenderPipeline;

		Registry<RenderPass> m_RenderPassRegistry;
		Registry<RenderPassProcessor> m_RenderPassProcessorRegistry;
		std::map<std::string, std::unique_ptr<RenderPipeline>> m_RenderPipelines;

	public:
		
		template<class T>
		void registerRenderPassType(const std::string& name) {
			m_RenderPassRegistry.registerFactory<T>(name);
		}

		template<class T>
		void registerRenderPassProcessorType(const std::string& name) {
			m_RenderPassProcessorRegistry.registerFactory<T>(name);
		}

		std::shared_ptr<RenderPass> createRenderPass(const std::string& name) {
			return m_RenderPassRegistry.create(name);
		}

		std::shared_ptr<RenderPassProcessor> createRenderPassProcessor(const std::string& name) {
			return m_RenderPassProcessorRegistry.create(name);
		}

		RenderPipeline* createRenderPipeline(const std::string& name) {
			auto it = m_RenderPipelines.find(name);
			if (it == m_RenderPipelines.end()) {
				m_RenderPipelines[name] = std::make_unique<RenderPipeline>();
			}
			return m_RenderPipelines[name].get();
 		}
		
		bool init(const RendererDescriptor& descriptor);
		
		Swapchain* acquireSwapchain();
		CommandBuffer* acquireCommandBuffer();
		
		std::shared_ptr<VertexBuffer> createVertexBuffer();
		std::shared_ptr<RenderPipelineState> createRenderPipelineState();
		std::shared_ptr<Texture> createTexture();
		
		void setRenderPipeline(RenderPipeline renderPipeline);
		void update(float deltaTime);
	};

}

#endif