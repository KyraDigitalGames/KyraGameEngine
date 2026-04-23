#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIPIPELINESTATEOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIPIPELINESTATEOPENGL_HPP

#include "OpenGL.hpp"
#include "RHIShaderOpenGL.hpp"
#include <KyraGameEngine/Renderer/RHI/RHIPipelineState.hpp>

namespace kyra {

	class RHIPipelineStateOpenGL : public RHIPipelineState {

		GLuint m_ShaderProgram = 0;
		GLuint m_VAO = 0;

		RHIPipelineState::BufferLayout m_BufferLayout;

	public:
		~RHIPipelineStateOpenGL() {
			if (m_VAO) {
				glDeleteVertexArrays(1, &m_VAO);
			}
			if (m_ShaderProgram) {
				glDeleteProgram(m_ShaderProgram);
			}
		}

		virtual bool init(const RHIPipelineState::Descriptor& descriptor) {
			if (m_ShaderProgram) {
				glDeleteProgram(m_ShaderProgram);
			}
			m_ShaderProgram = glCreateProgram();
			glAttachShader(m_ShaderProgram, static_cast<RHIShaderOpenGL*>(descriptor.vertexShader->get())->getId());
			glAttachShader(m_ShaderProgram, static_cast<RHIShaderOpenGL*>(descriptor.fragmentShader->get())->getId());
			glLinkProgram(m_ShaderProgram);
			GLint success = 0;
			glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
			if (!success) {
				GLint length = 0;
				glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &length);
				std::string errorMsg;
				errorMsg.resize(length);
				glGetProgramInfoLog(m_ShaderProgram, length, nullptr, &errorMsg[0]);
				std::cout << "Failed link shader program: " << errorMsg << std::endl;
				return false;
			}
			glGenVertexArrays(1, &m_VAO);
			m_BufferLayout = descriptor.bufferLayout;
			return true;
		}

		void bind() {
			glUseProgram(m_ShaderProgram);
			glBindVertexArray(m_VAO);
			for (auto& attribute : m_BufferLayout.attributes) {
				glVertexAttribPointer(attribute.id, attribute.elements, GL_FLOAT, GL_FALSE, m_BufferLayout.stride, (void*)attribute.offset);
				glEnableVertexAttribArray(attribute.id);
			}
		}

	};

}

#endif