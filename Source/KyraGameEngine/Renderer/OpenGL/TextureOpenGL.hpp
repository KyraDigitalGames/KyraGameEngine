#ifndef KYRAGAMEENGINE_RENDERER_OPENGL_TEXTUREOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_OPENGL_TEXTUREOPENGL_HPP

#include <KyraGameEngine/Renderer/Texture.hpp>
#include <glad/glad.h>

namespace kyra {

	class TextureOpenGL : public Texture {

		GLuint m_Id = 0;

	public:
		~TextureOpenGL();

		void upload(const Image* image);
		void bind();


	};

}

#endif