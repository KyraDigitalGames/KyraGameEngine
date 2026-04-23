#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIBUFFEROPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIBUFFEROPENGL_HPP

#include "OpenGL.hpp"
#include <KyraGameEngine/Renderer/RHI/RHIBuffer.hpp>

namespace kyra {

	class RHIBufferOpenGL : public RHIBuffer {

		GLuint m_Id = 0;
		RHIBuffer::Type m_Type = RHIBuffer::Type::Vertex;

	public:
		~RHIBufferOpenGL() {
			glDeleteBuffers(1, &m_Id);
		}

		bool init(const RHIBuffer::Descriptor& descriptor) final {
			if (descriptor.usage == RHIBuffer::Type::Vertex) {
				glGenBuffers(1, &m_Id);
				glBindBuffer(GL_ARRAY_BUFFER, m_Id);
				glBufferData(GL_ARRAY_BUFFER, descriptor.size, nullptr, GL_DYNAMIC_DRAW);
			}
			else {
				return false;
			}
			return true;
		}

		void upload(void* data, std::size_t size) final {
			if (m_Type == RHIBuffer::Type::Vertex) {
				glBindBuffer(GL_ARRAY_BUFFER, m_Id);
				glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
			}
		}

		void bind() {
			if (m_Type == RHIBuffer::Type::Vertex) {
				glBindBuffer(GL_ARRAY_BUFFER, m_Id);
			}
		}

	};

}

#endif