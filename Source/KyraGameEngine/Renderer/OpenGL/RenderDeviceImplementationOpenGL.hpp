#ifndef KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATIONOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATIONOPENGL_HPP

#include <KyraGameEngine/Renderer/RenderDeviceImplementation.hpp>
#include "SwapchainOpenGL.hpp"
#include "CommandBufferOpenGL.hpp"

namespace kyra {

	class RenderDeviceImplementationOpenGL : public RenderDeviceImplementation {

		SwapchainOpenGL m_Swapchain;
		CommandBufferOpenGL m_CommandBuffer;

	public:
		virtual ~RenderDeviceImplementationOpenGL() = default;
		
		bool init(RenderDeviceDescriptor& renderDeviceDescriptor) final;

		std::shared_ptr<VertexBuffer> createVertexBuffer();
		std::shared_ptr<RenderPipelineState> createRenderPipelineState();
		std::shared_ptr<Texture> createTexture();

		Swapchain* acquireSwapchain() final;
		CommandBuffer* acquireCommandBuffer() final;

	};

}

#endif