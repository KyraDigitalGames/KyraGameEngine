#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHISWAPCHAIN_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHISWAPCHAIN_HPP

#include "RHIFrameBuffer.hpp"
#include <memory>

namespace kyra {
	
	class RHISwapChain {

	public:
		virtual ~RHISwapChain() = default;

		struct Descriptor {
			int width = 0;
			int height = 0;
		};

		using Ptr = std::unique_ptr<RHISwapChain>;

		virtual bool init(const RHISwapChain::Descriptor& descriptor) = 0;
		virtual uint32_t acquireNextImage() = 0;
		virtual RHIFrameBuffer* getFrameBuffer(uint32_t index) = 0;
		virtual void present(uint32_t index) = 0;
	};

}

#endif