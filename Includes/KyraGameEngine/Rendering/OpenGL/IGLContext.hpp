#ifndef KYRAGAMEENGINE_RENDERING_OPENGL_IGLCONTEXT_HPP
#define KYRAGAMEENGINE_RENDERING_OPENGL_IGLCONTEXT_HPP	

namespace kyra {

	class IGLContext {
		
		public:
		virtual ~IGLContext() = default;

		virtual bool create(const IWindow& window) = 0;

		virtual void swapBuffers() = 0;

	};

}

#endif