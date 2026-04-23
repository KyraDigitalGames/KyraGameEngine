#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_OPENGLCONTEXT_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_OPENGLCONTEXT_HPP

#include <KyraGameEngine/Window/Window.hpp>
#include <memory>

namespace kyra {

	class OpenGLContext {

	public:
		virtual ~OpenGLContext() = default;

		using Ptr = std::unique_ptr<OpenGLContext>;

		static OpenGLContext::Ptr create();

		virtual bool init(Window::Ptr& window) = 0;
		virtual void swapBuffers() = 0;
	};

}

#endif