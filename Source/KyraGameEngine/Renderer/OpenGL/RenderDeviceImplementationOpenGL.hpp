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
		Swapchain* acquireSwapchain() final;
		CommandBuffer* acquireCommandBuffer() final;

	};

}

#endif