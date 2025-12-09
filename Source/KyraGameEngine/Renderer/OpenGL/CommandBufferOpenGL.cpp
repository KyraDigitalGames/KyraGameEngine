#include "CommandBufferOpenGL.hpp"
#include "RenderPipelineStateOpenGL.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <KyraGameEngine/Math/Matrix4.hpp>

namespace kyra {

	void CommandBufferOpenGL::clear(float r, float g, float b, float a) {
		glViewport(0, 0, 1280, 720);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void CommandBufferOpenGL::bindVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
		vertexBuffer->bind();
		m_BoundVertexBuffer = vertexBuffer;
	}
	
	void CommandBufferOpenGL::updateBuffer(std::shared_ptr<VertexBuffer> vertexBuffer, const VertexBufferDescriptor& descriptor) {
		vertexBuffer->bind();
		m_BoundVertexBuffer = vertexBuffer;
		vertexBuffer->update(descriptor.size, descriptor.data);
	}

	void CommandBufferOpenGL::bindRenderPipelineState(std::shared_ptr<RenderPipelineState> renderPipelineState) {
		renderPipelineState->bind();
		m_BoundRenderPipelineState = renderPipelineState;
	}

	void CommandBufferOpenGL::draw(std::size_t offset, std::size_t count) {
		if (m_BoundVertexBuffer && m_BoundRenderPipelineState) {
			static_cast<RenderPipelineStateOpenGL*>(m_BoundRenderPipelineState.get())->bindVertexBuffer(m_BoundVertexBuffer);
			glDrawArrays(GL_TRIANGLES, offset, count);
		}
	}

	void CommandBufferOpenGL::setUniformMat4(std::shared_ptr<RenderPipelineState> renderPipeline, const std::string& id, const Matrix4& matrix) {
		if (!renderPipeline) {
			return;
		}
		if (renderPipeline != m_BoundRenderPipelineState) {
			renderPipeline->bind();
			m_BoundRenderPipelineState = renderPipeline;
		}
		renderPipeline->uploadUniform(id.c_str(), matrix);
	}


}