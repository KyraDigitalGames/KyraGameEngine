#include "SwapchainOpenGL.hpp"

#include <KyraGameEngine/Log/Logger.hpp>
#include <KyraGameEngine/Debug/Profiling.hpp>

namespace kyra {
	
	SwapchainOpenGL::~SwapchainOpenGL() {
		KYRA_PROFILE_FUNCTION();
		if (m_RenderContext) {
			wglDeleteContext(m_RenderContext);
		}
		DeleteDC(m_DeviceContext);
	}

	bool SwapchainOpenGL::init(SwapchainDescriptor& descriptor) {
		KYRA_PROFILE_FUNCTION();
		if (descriptor.window == nullptr) {
			return false;
		}
		m_DeviceContext = GetDC(reinterpret_cast<HWND>(descriptor.window->getHandle()));
		KYRA_LOG_INFO("Create Device Context: " << m_DeviceContext);

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
		KYRA_LOG_INFO("Choose Pixelformat: " << pixelformat);

		if (!SetPixelFormat(m_DeviceContext, pixelformat, &pfd)) {
			KYRA_LOG_FATAL("Failed to set pixelformat");
			return false;
		}

		HGLRC temporaryContext = wglCreateContext(m_DeviceContext);
		wglMakeCurrent(m_DeviceContext, temporaryContext);
		
		if (!gladLoadWGL(m_DeviceContext)) {
			KYRA_LOG_FATAL("Failed to load WGL functions");
			wglDeleteContext(temporaryContext);
			return false;
		}
		
		int attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		m_RenderContext = wglCreateContextAttribsARB(m_DeviceContext, NULL, attributes);
		wglMakeCurrent(m_DeviceContext, m_RenderContext);
		wglDeleteContext(temporaryContext);


		if (!gladLoadGL()) {
			return false;
		}			
		return true;
	}

	void SwapchainOpenGL::setVSync(bool enabled) {
		KYRA_PROFILE_FUNCTION();
		wglSwapIntervalEXT((enabled) ? 1 : 0);
	}


	void SwapchainOpenGL::swap() {
		KYRA_PROFILE_FUNCTION();
		SwapBuffers(m_DeviceContext);
	}

}