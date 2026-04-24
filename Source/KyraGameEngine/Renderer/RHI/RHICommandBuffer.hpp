#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHICOMMANDBUFFER_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHICOMMANDBUFFER_HPP

#include "RHIFrameBuffer.hpp"
#include "RHIRenderPass.hpp"
#include "RHIBuffer.hpp"
#include "RHIPipelineState.hpp"

namespace kyra {

	class RHICommandBuffer {

	public:
		virtual ~RHICommandBuffer() = default;

		using Ptr = std::unique_ptr<RHICommandBuffer>;

		virtual void begin() = 0;
		virtual void beginRenderPass(RHIRenderPass::Ptr& renderPass, RHIFrameBuffer* framebuffer) = 0;
		virtual void bindPipeline(RHIPipelineState::Ptr& pipeline) = 0;
		virtual void bindPipeline(RHIPipelineState* pipeline) = 0;
		virtual void bindVertexBuffer(int index, RHIBuffer::Ptr& buffer) = 0;
		virtual void bindVertexBuffer(int index, RHIBuffer* buffer) = 0;
		virtual void draw(int offset, int count) = 0;
		virtual void endRenderPass() = 0;
		virtual void end() = 0;
	};
}

#endif