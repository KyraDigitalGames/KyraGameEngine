#ifndef KYRAGAMEENGINE_RENDERER_RENDERER_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERER_HPP

#include "RenderPipeline.hpp"
#include "RenderDeviceImplementation.hpp"
#include "VertexBuffer.hpp"
#include "RenderPipelineState.hpp"
#include <KyraGameEngine/Window/Window.hpp>
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

	class Renderer {

		std::unique_ptr<RenderDeviceImplementation> m_Implementation;
		RenderPipeline m_RenderPipeline;

	public:
		
		
		bool init(const RendererDescriptor& descriptor);
		
		Swapchain* acquireSwapchain();
		CommandBuffer* acquireCommandBuffer();
		
		std::shared_ptr<VertexBuffer> createVertexBuffer();
		std::shared_ptr<RenderPipelineState> createRenderPipelineState();
		
		void setRenderPipeline(RenderPipeline renderPipeline);
		void update();
	};

}

#endif