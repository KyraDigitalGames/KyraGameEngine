#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHICOMMANDQUEUE_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHICOMMANDQUEUE_HPP

#include "RHICommandBuffer.hpp"

namespace kyra {

	class RHICommandQueue {

	public:
		virtual ~RHICommandQueue() = default;

		using Ptr = std::unique_ptr<RHICommandQueue>;

		virtual void submit(RHICommandBuffer::Ptr& buffer) = 0;

	};

}

#endif