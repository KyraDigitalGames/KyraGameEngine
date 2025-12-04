#ifndef KYRAGAMEENGINE_RENDERER_OPENGL_VERTEXBUFFEROPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_OPENGL_VERTEXBUFFEROPENGL_HPP


#include <glad/glad.h>
#include <KyraGameEngine/Renderer/VertexBuffer.hpp>

namespace kyra {

	class VertexBufferOpenGL : public VertexBuffer {

		GLuint m_Id = 0;
		
	public:
		~VertexBufferOpenGL();

		bool init(const VertexBufferDescriptor& descriptor) final;
		void bind() final;

		constexpr GLuint getId() const {
			return m_Id;
		}

	};

}

#endif