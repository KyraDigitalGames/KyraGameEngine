#include "RenderDeviceImplementationOpenGL.hpp"

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

}