
#include "ShaderProgramOpenGL.hpp"
#include <KyraGameEngine/IO/TextFile.hpp>

namespace kyra {

	bool ShaderProgramOpenGL::loadShader(const std::filesystem::path& file, GLenum type, ShaderOpenGL& shader) {
		TextFile textFile;
		if(!textFile.open(file.string())) {
			return false;
		}
		if(!shader.init(type, textFile.getContent().c_str())) {
			return false;
		}
		textFile.close();
		return true;
	}
		
	ShaderProgramOpenGL::~ShaderProgramOpenGL() {
		if(m_Id) {
			glDeleteProgram(m_Id);
		}
	}		
	
	/// \todo Error checking
	bool ShaderProgramOpenGL::init(const ShaderDescriptionGLSL& shaderDescription) {
			
		if(m_Id) {
			glDeleteProgram(m_Id);
		}
			
		ShaderOpenGL vertexShader;
		if(!loadShader(shaderDescription.vertexShader, GL_VERTEX_SHADER, vertexShader)) {
			return false;
		}
			
		ShaderOpenGL fragmentShader;
		if(!loadShader(shaderDescription.fragmentShader, GL_FRAGMENT_SHADER, fragmentShader)) {
			return false;
		}
			
		m_Id = glCreateProgram();
		glAttachShader(m_Id, vertexShader.getId());
		glAttachShader(m_Id, fragmentShader.getId());
		glLinkProgram(m_Id);
			
		return true;
	}	
		
	/// \todo Implementation
	bool ShaderProgramOpenGL::init(const ShaderDescriptionHLSL& shaderDescription) {
		return false;
	}
		
	/// \todo Implementation
	bool ShaderProgramOpenGL::init(const ShaderDescriptionSPIRV& shader) {
		return false;
	}
	
	void ShaderProgramOpenGL::bind() {
		glUseProgram(m_Id);
	}
	
}
