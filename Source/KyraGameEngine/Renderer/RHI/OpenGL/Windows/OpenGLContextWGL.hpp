#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_WINDOWS_OPENGLCONTEXTWGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_WINDOWS_OPENGLCONTEXTWGL_HPP

#include <KyraGameEngine/Renderer/RHI/OpenGL/OpenGL.hpp>
#include <KyraGameEngine/Renderer/RHI/OpenGL/OpenGLContext.hpp>
#include <Windows.h>

namespace kyra {

	class OpenGLContextWGL : public OpenGLContext {

		HDC m_DeviceContext;
		HGLRC m_RenderContext;

	public:
		~OpenGLContextWGL() {
			if (m_RenderContext) {
				wglDeleteContext(m_RenderContext);
			}
			if (m_DeviceContext) {
				DeleteDC(m_DeviceContext);
			}
		}

		virtual bool init(Window::Ptr& window) {
			m_DeviceContext = GetDC(reinterpret_cast<HWND>(window->getHandle()));
			if (!m_DeviceContext) {
				return false;
			}
			PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cStencilBits = 16;
			pfd.cDepthBits = 16;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int pixelformat = ChoosePixelFormat(m_DeviceContext, &pfd);
			if (!pixelformat) {
				return false;
			}

			if (!SetPixelFormat(m_DeviceContext, pixelformat, &pfd)) {
				return false;
			}

			m_RenderContext = wglCreateContext(m_DeviceContext);
			wglMakeCurrent(m_DeviceContext, m_RenderContext);

			if (!gl::init()) {
				return false;
			}

			return true;
		}

		virtual void swapBuffers() {
			SwapBuffers(m_DeviceContext);
		}

	};

}

#endif