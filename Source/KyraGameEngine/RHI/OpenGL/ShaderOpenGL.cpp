
#include "ShaderOpenGL.hpp"
#include <KyraGameEngine/Platform/MessageBox.hpp>
#include <format>

namespace kyra {
	
	ShaderOpenGL::~ShaderOpenGL() {
		if(m_Id) {
			glDeleteShader(m_Id);
		}
	}
		
	bool ShaderOpenGL::init(GLenum shaderType, const char* sourceCode) {
		if(m_Id) {
			glDeleteShader(m_Id);
		}
		m_Id = glCreateShader(shaderType);
		glShaderSource(m_Id, 1, &sourceCode, NULL);
		glCompileShader(m_Id);
		int success = 0;
		glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
		if(!success) {
			GLint logSize = 0;
			glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &logSize);
			std::string errorMsg;
			errorMsg.resize(logSize);
			glGetShaderInfoLog(m_Id, logSize, NULL, &errorMsg[0]);
			MessageBox::showError("Kyra Game Engine", std::format("Failed compile shader : {} \n {}", errorMsg.c_str(), sourceCode));
			return false;
		}
		return true;
	}
		
}