#ifndef KYRAGAMEENGINE_RHI_ABSTRACTSHADERPROGRAM_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTSHADERPROGRAM_HPP

#include <filesystem>

namespace kyra {	

	struct ShaderDescriptionGLSL {
		std::filesystem::path vertexShader;
		std::filesystem::path fragmentShader;	
	};
	
	struct ShaderDescriptionHLSL {
		std::filesystem::path path;
	};
	
	struct ShaderDescriptionSPIRV {
		std::filesystem::path vertexShader;
		std::filesystem::path fragmentShader;
	};
	
	class AbstractShaderProgram {
		
		public:
		virtual ~AbstractShaderProgram() = default;
		
		[[nodiscard]] virtual bool init(const ShaderDescriptionGLSL& shaderDescription) = 0;
		
		[[nodiscard]] virtual bool init(const ShaderDescriptionHLSL& shaderDescription) = 0;

		[[nodiscard]] virtual bool init(const ShaderDescriptionSPIRV& shaderDescription) = 0;

		virtual void bind() = 0;
		
	};
}

#endif