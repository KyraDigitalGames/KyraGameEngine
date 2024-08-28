
#include <iostream>
#include "PipelineOpenGL.hpp"


namespace kyra {
	
	constexpr GLenum toGLAttributeType(BufferElementType type) {
		return GL_FLOAT;
	}
	
	bool PipelineOpenGL::init(const PipelineDescriptor& pipeline) {
		m_ShaderProgram = pipeline.shaderProgram;
		m_Layout = pipeline.bufferLayout;
		return true;
	}
	
	void PipelineOpenGL::bind() {
		glBindVertexArray(m_Id);
		std::size_t id = 0;
		for(auto entry : m_Layout) {
			glVertexAttribPointer(id, entry.count, toGLAttributeType(entry.type), entry.normalised, m_Layout.getSize(), (void*)entry.offset);
			glEnableVertexAttribArray(id); 
			id++;
		}
		m_ShaderProgram->bind();
	}

}
