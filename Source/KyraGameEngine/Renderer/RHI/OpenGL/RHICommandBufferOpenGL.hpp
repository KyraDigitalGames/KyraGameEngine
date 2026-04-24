#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHICOMMANDQUEUEOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHICOMMANDQUEUEOPENGL_HPP

#include "RHIBufferOpenGL.hpp"
#include "RHIPipelineStateOpenGL.hpp"
#include <KyraGameEngine/Renderer/RHI/RHICommandQueue.hpp>
#include <KyraGameEngine/Renderer/RHI/RHICommandBuffer.hpp>

namespace kyra {

	class RHICommandBufferOpenGL : public  RHICommandBuffer {

		RHIPipelineStateOpenGL* m_PipelineState = nullptr;
		RHIBufferOpenGL* m_VertexBuffer = nullptr;

	public:
		virtual ~RHICommandBufferOpenGL() = default;

		virtual void begin() {
			m_PipelineState = nullptr;
		}

		virtual void beginRenderPass(RHIRenderPass::Ptr& renderPass, RHIFrameBuffer* framebuffer) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		virtual void bindPipeline(RHIPipelineState::Ptr& pipeline) {
			if (m_PipelineState != pipeline.get()) {
				m_PipelineState = static_cast<RHIPipelineStateOpenGL*>(pipeline.get());
			}
		}

		virtual void bindPipeline(RHIPipelineState* pipeline) {
			if (m_PipelineState != pipeline) {
				m_PipelineState = static_cast<RHIPipelineStateOpenGL*>(pipeline);
			}
		}

		virtual void bindVertexBuffer(int index, RHIBuffer::Ptr& buffer) {
			if (m_VertexBuffer != buffer.get()) {
				m_VertexBuffer = static_cast<RHIBufferOpenGL*>(buffer.get());
			}
		}

		virtual void bindVertexBuffer(int index, RHIBuffer* buffer) {
			m_VertexBuffer = static_cast<RHIBufferOpenGL*>(buffer);
		}

		virtual void draw(int offset, int count) {
			if (!m_VertexBuffer) {
				return;
			}
			m_VertexBuffer->bind();
			if (!m_PipelineState) {
				return;
			}
			m_PipelineState->bind();
			glDrawArrays(GL_TRIANGLES, offset, count);
		}

		virtual void endRenderPass() {

		}

		virtual void end() {

		}

	};



}

#endif