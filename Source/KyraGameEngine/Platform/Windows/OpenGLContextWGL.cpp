
#include "OpenGLContextWGL.hpp"
#include <KyraGameEngine/Platform/MessageBox.hpp>
#include <format>

namespace kyra {
	
	OpenGLContextWGL::~OpenGLContextWGL() {
		if(m_RenderContext) {
			wglDeleteContext(m_RenderContext);
		}
		if(m_DeviceContext) {
			DeleteDC(m_DeviceContext);
		}
	}
		
	bool OpenGLContextWGL::init(const AbstractWindow& window) {
			
		m_DeviceContext = GetDC( reinterpret_cast<HWND>(window.getHandle()) );
		if(!m_DeviceContext) {
			MessageBox::showError("Kyra Game Engine", std::format("Failed to create device context ( {} )", GetLastError()));			
			return false;
		}
			
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;
	
		int pixelformat = ChoosePixelFormat(m_DeviceContext, &pfd);
		if(!pixelformat) {
			MessageBox::showError("Kyra Game Engine", std::format("Failed to choose pixelformat ( {} )", GetLastError()));			
			return false;
		}
			
		if(!SetPixelFormat(m_DeviceContext, pixelformat, &pfd)) {
			MessageBox::showError("Kyra Game Engine", std::format("Failed to set pixelformat ( {} )", GetLastError()));			
			return false;
		}
			
		HGLRC temporaryContext = wglCreateContext(m_DeviceContext);
		if(!temporaryContext) {
			MessageBox::showError("Kyra Game Engine", std::format("Failed to create temporary OpenGL context ( {} )", GetLastError()));			
			return false;
		}
		wglMakeCurrent(m_DeviceContext, temporaryContext);
			
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)(wglGetProcAddress("wglCreateContextAttribsARB"));	
		
		const int attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 2,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		
		m_RenderContext = wglCreateContextAttribsARB(m_DeviceContext, nullptr, attributes);
		if(!m_RenderContext) {
			MessageBox::showError("Kyra Game Engine", std::format("Failed to create OpenGL context ( {} )", GetLastError()));			
			return false;
		}
		wglMakeCurrent(m_DeviceContext,m_RenderContext);
		
		if(!glex::init(wglGetProcAddress)) {
			MessageBox::showError("Kyra Game Engine", "Failed to initialise GLEX");			
			wglDeleteContext(temporaryContext);
			return false;
		}
		
		wglDeleteContext(temporaryContext);
		return true;
	}
		
	void OpenGLContextWGL::swapBuffers() {
		SwapBuffers(m_DeviceContext);
	}
			
}

