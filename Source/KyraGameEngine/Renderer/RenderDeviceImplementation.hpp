#ifndef KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATION_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERDEVICEIMPLEMENTATION_HPP

#include "Swapchain.hpp"
#include "CommandBuffer.hpp"
#include <memory>


namespace kyra {

	struct RenderDeviceDescriptor {
		Window* window = nullptr;
	};

	class RenderDeviceImplementation {

	public:
		virtual ~RenderDeviceImplementation() = default;

		virtual bool init(RenderDeviceDescriptor& renderDeviceDescriptor) = 0;
		virtual Swapchain* acquireSwapchain() = 0;
		virtual CommandBuffer* acquireCommandBuffer() = 0;
	};

}

#endif