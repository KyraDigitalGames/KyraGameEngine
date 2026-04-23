#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHISHADEROPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHISHADEROPENGL_HPP

#include "OpenGL.hpp"
#include <KyraGameEngine/Renderer/RHI/RHIShader.hpp>

#include <string>
#include <iostream>

namespace kyra {

	class RHIShaderOpenGL : public RHIShader {

		GLuint m_Id = 0;

	public:
		~RHIShaderOpenGL() {
			if (m_Id) {
				glDeleteShader(m_Id);
			}
		}

		bool init(const RHIShader::Descriptor& descriptor) final {
			if (m_Id) {
				glDeleteShader(m_Id);
			}
			if (descriptor.data == nullptr) {
				return false;
			}
			GLenum shaderType = (descriptor.type == RHIShader::Type::Vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
			m_Id = glCreateShader(shaderType);
			glShaderSource(m_Id, 1, &descriptor.data, nullptr);
			glCompileShader(m_Id);
			GLint success = 0;
			glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLint length = 0;
				glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &length);
				std::string errorMsg;
				errorMsg.resize(length);
				glGetShaderInfoLog(m_Id, length, nullptr, &errorMsg[0]);
				std::cout << "Failed to compile shader: " << errorMsg << std::endl;
				std::cout << std::string(descriptor.data) << std::endl;
				return false;
			}
			return true;
		}

		GLuint getId() const {
			return m_Id;
		}
	};


}

#endif