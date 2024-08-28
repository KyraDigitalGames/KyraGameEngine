
#include "ShaderOpenGL.hpp"

namespace kyra {
	
	ShaderOpenGL::~ShaderOpenGL() {
		if(m_Id) {
			glDeleteShader(m_Id);
		}
	}
		
	/// \todo Use a platform independent message box class
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
			MessageBoxA(NULL, errorMsg.c_str(), "Kyra Game Engine", MB_OK);
			return false;
		}
		return true;
	}
		
}