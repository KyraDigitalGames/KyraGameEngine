#ifndef KYRAGAMEENGINE_RENDERING_OPENGL_RENDERPIPELINESTATEOPENGL_HPP
#define KYRAGAMEENGINE_RENDERING_OPENGL_RENDERPIPELINESTATEOPENGL_HPP


#include <KyraGameEngine/Log/Logger.hpp>

#include <glad/glad.h>
#include <KyraGameEngine/Renderer/RenderPipelineState.hpp>
#include <string>
#include <map>
#include "VertexBufferOpenGL.hpp"
#include <KyraGameEngine/Math/Matrix4.hpp>

namespace kyra {


	class RenderPipelineStateOpenGL : public RenderPipelineState {

		std::map<GLuint, GLuint> m_VAOCache;
		GLuint m_ShaderProgram = 0;

		static GLuint createShader(GLenum type, const char* sourceCode) {
			GLuint id = glCreateShader(type);
			glShaderSource(id, 1, &sourceCode, nullptr);
			glCompileShader(id);
			GLint result = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (!result) {
				GLint length = 0;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				std::string text;
				text.resize(length);
				glGetShaderInfoLog(id, length, nullptr, &text[0]);
				KYRA_LOG_ERROR("[ERROR] " << text);
				glDeleteShader(id);
				return 0;
			}
			return id;
		}


	public:
		~RenderPipelineStateOpenGL();


		bool init(const RenderPipelineStateDescriptor& descriptor) final;
		void bind() final;

		void uploadUniform(const char* name, const Matrix4& matrix) {
			int loc = glGetUniformLocation(m_ShaderProgram, name);
			glUniformMatrix4fv(loc, 1, GL_FALSE, matrix.getDataPtr());
		}

		// Internal for OpenGL only
		void bindVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
			auto it = m_VAOCache.find(static_cast<VertexBufferOpenGL*>(vertexBuffer.get())->getId());
			if (it == m_VAOCache.end()) {
				vertexBuffer->bind();
				GLuint vao = 0;
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
				m_VAOCache[static_cast<VertexBufferOpenGL*>(vertexBuffer.get())->getId()] = vao;
				return;
			}
			glBindVertexArray(it->second);
		}
		

	};

}

#endif