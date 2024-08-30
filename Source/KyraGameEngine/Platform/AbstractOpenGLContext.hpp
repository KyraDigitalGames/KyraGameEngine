#ifndef KYRAGAMEENGINE_RHI_OPENGL_ABSTRACTOPENGLCONTEXT_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_ABSTRACTOPENGLCONTEXT_HPP

#include <KyraGameEngine/Platform/AbstractWindow.hpp>

namespace kyra {
	
	class AbstractOpenGLContext {
		
		public:
		virtual ~AbstractOpenGLContext() = default;
		
		[[nodiscard]] virtual bool init(const AbstractWindow& window) = 0;
		virtual void swapBuffers() = 0;
		
	};
	
}

#endif