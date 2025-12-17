#include "RenderDeviceImplementationOpenGL.hpp"
#include "VertexBufferOpenGL.hpp"
#include "RenderPipelineStateOpenGL.hpp"
#include <KyraGameEngine/Debug/Profiling.hpp>

namespace kyra {

	bool RenderDeviceImplementationOpenGL::init(RenderDeviceDescriptor& renderDeviceDescriptor) {
		KYRA_PROFILE_FUNCTION();
		SwapchainDescriptor swapchainDescriptor;
		swapchainDescriptor.window = renderDeviceDescriptor.window;
		return m_Swapchain.init(swapchainDescriptor);
	}

	Swapchain* RenderDeviceImplementationOpenGL::acquireSwapchain() {
		KYRA_PROFILE_FUNCTION();
		return &m_Swapchain;
	}


	CommandBuffer* RenderDeviceImplementationOpenGL::acquireCommandBuffer() {
		KYRA_PROFILE_FUNCTION();
		return &m_CommandBuffer;
	}


	std::shared_ptr<VertexBuffer> RenderDeviceImplementationOpenGL::createVertexBuffer() {
		KYRA_PROFILE_FUNCTION();
		return std::make_shared<VertexBufferOpenGL>();
	}


	std::shared_ptr<RenderPipelineState> RenderDeviceImplementationOpenGL::createRenderPipelineState() {
		KYRA_PROFILE_FUNCTION();
		return std::make_shared<RenderPipelineStateOpenGL>();
	}


}