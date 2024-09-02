#include "CommandBufferOpenGL.hpp"

namespace kyra {
	
	void CommandBufferOpenGL::bindPipeline(AbstractPipeline* pipeline) {	
		m_Pipeline = pipeline;
	}

	void CommandBufferOpenGL::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
		
	void CommandBufferOpenGL::bindVertexBuffer(AbstractVertexBuffer* vertexBuffer) {
		m_VertexBuffer = vertexBuffer;
	}
	
	void CommandBufferOpenGL::draw(int firstVertex, int numVertices) {
		if(m_BoundVertexBuffer != m_VertexBuffer) {
			m_BoundVertexBuffer = m_VertexBuffer;
			m_BoundVertexBuffer->bind();
		}
		if(m_BoundPipeline != m_Pipeline) {
			m_BoundPipeline = m_Pipeline;
			m_BoundPipeline->bind();
		}
		GLEX_CHECK(glDrawArrays(GL_TRIANGLES, firstVertex, numVertices));
	}
		
}
