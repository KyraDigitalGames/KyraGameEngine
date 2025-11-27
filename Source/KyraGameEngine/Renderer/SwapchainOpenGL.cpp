#include "SwapchainOpenGL.hpp"

namespace kyra {
	
	SwapchainOpenGL::~SwapchainOpenGL() {
		if (m_RenderContext) {
			wglDeleteContext(m_RenderContext);
		}
		DeleteDC(m_DeviceContext);
	}

	bool SwapchainOpenGL::init(SwapchainDescriptor& descriptor) {
		if (descriptor.window == nullptr) {
			return false;
		}
		m_DeviceContext = GetDC(reinterpret_cast<HWND>(descriptor.window->getHandle()));

		PIXELFORMATDESCRIPTOR pfd = { 0 };
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.cColorBits = 32;
		pfd.cStencilBits = 24;
		pfd.cDepthBits = 16;
		pfd.iPixelType = PFD_TYPE_RGBA;
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
		return true;
	}

	void SwapchainOpenGL::swap() {
		SwapBuffers(m_DeviceContext);
	}

}