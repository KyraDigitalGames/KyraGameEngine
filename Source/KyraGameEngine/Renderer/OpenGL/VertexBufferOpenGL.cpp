#include "VertexBufferOpenGL.hpp"
#include <KyraGameEngine/Debug/Profiling.hpp>

namespace kyra {

	VertexBufferOpenGL::~VertexBufferOpenGL() {
		KYRA_PROFILE_FUNCTION();
		if (m_Id) {
			glDeleteBuffers(1, &m_Id);
		}
	}


	bool VertexBufferOpenGL::init(const VertexBufferDescriptor& descriptor)  {
		KYRA_PROFILE_FUNCTION();
		if (m_Id) {
			glDeleteBuffers(1, &m_Id);
		}
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, descriptor.size, descriptor.data, GL_STATIC_DRAW);
		return true;
	}

	void VertexBufferOpenGL::update(std::size_t size, void* data) {
		KYRA_PROFILE_FUNCTION();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void VertexBufferOpenGL::bind() {
		KYRA_PROFILE_FUNCTION();
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}

}