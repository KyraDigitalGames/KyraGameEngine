#ifndef KYRAGAMEENGINE_RHI_OPENGL_SHADERPROGRAM_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_SHADERPROGRAM_HPP

#include "GLEX.hpp"
#include "ShaderOpenGL.hpp"
#include <KyraGameEngine/RHI/AbstractShaderProgram.hpp>
#include <filesystem>

namespace kyra {
		
	class ShaderProgramOpenGL : public AbstractShaderProgram {
		
		GLuint m_Id = 0;
		
		bool loadShader(const std::filesystem::path& file, GLenum type, ShaderOpenGL& shader);
		
		public:
		virtual ~ShaderProgramOpenGL();
		
		[[nodiscard]] bool init(const ShaderDescriptionGLSL& shaderDescription) final;		
		
		[[nodiscard]] bool init(const ShaderDescriptionHLSL& shaderDescription) final;
	
		[[nodiscard]] bool init(const ShaderDescriptionSPIRV& shader) final;
				
		void bind() final;
		
	};
}

#endif