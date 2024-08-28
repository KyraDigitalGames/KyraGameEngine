#ifndef KYRAGAMEENGINE_RHI_OPENGL_SHADEROPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_SHADEROPENGL_HPP

#include "GLEX.hpp"

namespace kyra {
	
	class ShaderOpenGL {
		
		GLuint m_Id = 0;
		
		public:
		~ShaderOpenGL();
		
		[[nodiscard]] bool init(GLenum shaderType, const char* sourceCode);
		
		[[nodiscard]] constexpr GLuint getId() const {
			return m_Id;
		}
		
	};
}

#endif