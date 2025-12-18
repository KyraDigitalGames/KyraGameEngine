#include "TextureOpenGL.hpp"

namespace kyra {

	TextureOpenGL::~TextureOpenGL() {
		glDeleteTextures(1, &m_Id);
	}

	void TextureOpenGL::upload(const Image* image) {
		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (image->getChannels() == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());
		}
		else if (image->getChannels() == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getData());
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void TextureOpenGL::bind() {
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

}