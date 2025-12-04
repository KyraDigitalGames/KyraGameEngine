#include "RenderDeviceImplementationOpenGL.hpp"
#include "VertexBufferOpenGL.hpp"
#include "RenderPipelineStateOpenGL.hpp"

namespace kyra {

	bool RenderDeviceImplementationOpenGL::init(RenderDeviceDescriptor& renderDeviceDescriptor) {
		SwapchainDescriptor swapchainDescriptor;
		swapchainDescriptor.window = renderDeviceDescriptor.window;
		return m_Swapchain.init(swapchainDescriptor);
	}

	Swapchain* RenderDeviceImplementationOpenGL::acquireSwapchain() {
		return &m_Swapchain;
	}


	CommandBuffer* RenderDeviceImplementationOpenGL::acquireCommandBuffer() {
		return &m_CommandBuffer;
	}


	std::shared_ptr<VertexBuffer> RenderDeviceImplementationOpenGL::createVertexBuffer() {
		return std::make_shared<VertexBufferOpenGL>();
	}


	std::shared_ptr<RenderPipelineState> RenderDeviceImplementationOpenGL::createRenderPipelineState() {
		return std::make_shared<RenderPipelineStateOpenGL>();
	}


}