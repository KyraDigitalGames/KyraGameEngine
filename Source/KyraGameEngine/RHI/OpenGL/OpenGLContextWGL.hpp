#ifndef KYRAGAMEENGINE_RHI_OPENGL_OPENGLCONTEXTWGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_OPENGLCONTEXTWGL_HPP

#include "GLEX.hpp"
#include "AbstractOpenGLContext.hpp"
#include <windows.h>

namespace kyra {
	
	class OpenGLContextWGL : public AbstractOpenGLContext {
		
		HDC m_DeviceContext = NULL;
		HGLRC m_RenderContext = NULL;
		
		public:
		~OpenGLContextWGL();
		
		[[nodiscard]] bool init(const AbstractWindow& window) final;
		void swapBuffers() final;
			
	};
	
	using OpenGLContext = OpenGLContextWGL;

}

#endif