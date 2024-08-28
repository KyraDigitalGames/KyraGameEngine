
#include "VertexBufferOpenGL.hpp"

namespace kyra {
	
	VertexBufferOpenGL::VertexBufferOpenGL() {
		GLEX_CHECK(glGenBuffers(1,&m_Handle));
	}
		
	VertexBufferOpenGL::~VertexBufferOpenGL() {
		GLEX_CHECK(glDeleteBuffers(1, &m_Handle));
	}
		
	void VertexBufferOpenGL::resize(uint32_t size) {
		GLEX_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		GLEX_CHECK(glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW));
		m_Size = size;
	}
		
	void VertexBufferOpenGL::setData(uint32_t size, const void* data) {
		GLEX_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		GLEX_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
		m_Size = size;			
	}
		
	void VertexBufferOpenGL::setSubData(uint32_t size, const void* data, uint32_t offset) {
		if(size * offset <= m_Size) {
			GLEX_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
			GLEX_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
		}
	}
		
	void VertexBufferOpenGL::bind() {
		GLEX_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
	}
		
	void VertexBufferOpenGL::unbind() {
			GLEX_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
		
	uint32_t VertexBufferOpenGL::getSize() const {
		return m_Size;
	}

}
