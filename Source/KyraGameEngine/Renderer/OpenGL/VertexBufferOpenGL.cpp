#include "VertexBufferOpenGL.hpp"

namespace kyra {

	VertexBufferOpenGL::~VertexBufferOpenGL() {
		if (m_Id) {
			glDeleteBuffers(1, &m_Id);
		}
	}


	bool VertexBufferOpenGL::init(const VertexBufferDescriptor& descriptor)  {
		if (m_Id) {
			glDeleteBuffers(1, &m_Id);
		}
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, descriptor.size, descriptor.data, GL_STATIC_DRAW);
		return true;
	}

	void VertexBufferOpenGL::update(std::size_t size, void* data) {
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void VertexBufferOpenGL::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

}