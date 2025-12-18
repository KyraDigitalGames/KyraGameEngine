#ifndef KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATION_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATION_HPP

#include "Swapchain.hpp"
#include "CommandBuffer.hpp"
#include "VertexBuffer.hpp"
#include "RenderPipeline.hpp"
#include "RenderPipelineState.hpp"
#include "Texture.hpp"
#include <memory>


namespace kyra {

	struct RenderDeviceDescriptor {
		Window* window = nullptr;
	};

	class RenderDeviceImplementation {

	public:
		virtual ~RenderDeviceImplementation() = default;

		virtual bool init(RenderDeviceDescriptor& renderDeviceDescriptor) = 0;
		
		virtual std::shared_ptr<VertexBuffer> createVertexBuffer() = 0;
		virtual std::shared_ptr<RenderPipelineState> createRenderPipelineState() = 0;
		virtual std::shared_ptr<Texture> createTexture() = 0;

		virtual Swapchain* acquireSwapchain() = 0;
		virtual CommandBuffer* acquireCommandBuffer() = 0;
	};

}

#endif