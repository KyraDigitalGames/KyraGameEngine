#include "RenderPipelineStateOpenGL.hpp"

namespace kyra {


	RenderPipelineStateOpenGL::~RenderPipelineStateOpenGL() {
		for (auto& cache : m_VAOCache) {
			glDeleteVertexArrays(1, &cache.second);
		}
		if (m_ShaderProgram) {
			glDeleteProgram(m_ShaderProgram);
		}
	}

	bool RenderPipelineStateOpenGL::init(const RenderPipelineStateDescriptor& descriptor) {
		if (m_ShaderProgram) {
			glDeleteProgram(m_ShaderProgram);
		}

		std::vector<GLuint> shaderIds;
		bool error = false;
		for (auto& shader : descriptor.shaders) {
			GLuint shaderId = 0;
			if (shader.type == ShaderType::Vertex) {
				shaderId = createShader(GL_VERTEX_SHADER, shader.data);
				if (!shaderId) {
					error = true;
				}
			}
			else {
				shaderId = createShader(GL_FRAGMENT_SHADER, shader.data);
				if (!shaderId) {
					error = true;
				}
			}
			shaderIds.emplace_back(shaderId);
		}

		if (error) {
			return false;
		}

		m_ShaderProgram = glCreateProgram();
		for (auto& id : shaderIds) {
			glAttachShader(m_ShaderProgram, id);
		}
		glLinkProgram(m_ShaderProgram);
		for (auto& id : shaderIds) {
			glDeleteShader(m_ShaderProgram);
		}

		GLint result = 0;
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &result);
		if (!result) {
			GLint length = 0;
			glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &length);
			std::string text;
			text.resize(length);
			glGetProgramInfoLog(m_ShaderProgram, length, nullptr, &text[0]);
			KYRA_LOG_ERROR("[ERROR] " << text);
			return false;
		}
		return true;
	}
	
	void RenderPipelineStateOpenGL::bind() {
		glUseProgram(m_ShaderProgram);
	}
		

}