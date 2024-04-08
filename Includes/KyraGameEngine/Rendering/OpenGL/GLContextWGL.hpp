#ifndef KYRAGAMEENGINE_RENDERING_GLCONTEXTWGL_HPP
#define KYRAGAMEENGINE_RENDERING_GLCONTEXTWGL_HPP


#include "IGLContext.hpp"
#include <KyraGameEngine/GLEX.hpp>


namespace kyra {
	
	class GLContextWGL : public IGLContext {
		
		HDC m_DeviceContext = 0;
		HGLRC m_RenderContext = 0;
		
		public:
		virtual ~GLContextWGL() {
			if(m_RenderContext) {
				wglDeleteContext(m_RenderContext);
			}		
			if(m_DeviceContext) {
				DeleteDC(m_DeviceContext);
			}
		}
		
		virtual bool create(const IWindow& window) final {
			
			WindowSettings settings;
			settings.size = {0,0};
			settings.className = "KYRA_TEMPORARY_WINDOW";
			
			Window temporaryWindow;
			if(!temporaryWindow.create(settings)) {
				return false;
			}
			
			HDC temporaryDC = GetDC( reinterpret_cast<HWND>(temporaryWindow.getHandle()) );
			if(!temporaryDC) {
				KYRA_LOG_ERROR(GLContextWGL::create, "Failed to create device context ( " << GetLastError() << " )");
				return false;
			}
			
			PIXELFORMATDESCRIPTOR pfd;
			ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 16;
			pfd.cStencilBits = 8;
			pfd.iLayerType = PFD_MAIN_PLANE;
			
			int pixelformat = ChoosePixelFormat(temporaryDC, &pfd);
			if(!pixelformat) {
				KYRA_LOG_ERROR(GLContextWGL::create, "Failed to choose pixelformat ( " << GetLastError() << " )");
				return false;
			}

			if(!SetPixelFormat(temporaryDC, pixelformat, &pfd)) {
				KYRA_LOG_ERROR(GLContextWGL::create, "Failed to set pixelformat ( " << GetLastError() << " )");
				return false;
			}
			
			HGLRC temporaryRenderContext = wglCreateContext(temporaryDC);
			wglMakeCurrent(temporaryDC, temporaryRenderContext);
	
			wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		
			m_DeviceContext = GetDC( reinterpret_cast<HWND>(window.getHandle()) );
			if(!m_DeviceContext) {
				KYRA_LOG_ERROR(GLContextWGL::create, "Failed to create device context ( " << GetLastError() << " )");
				return false;
			}
			
		    int attribList[] = {
				WGL_SAMPLES_ARB, 0,
				WGL_SAMPLE_BUFFERS_ARB, 0,
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, 32,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				0
			};
			
			UINT numFormats;
			if ( !wglChoosePixelFormatARB(m_DeviceContext, attribList, NULL, 1, &pixelformat, &numFormats) || numFormats == 0)
			{
				KYRA_LOG_ERROR(GLContextWGL::create, "Failed to choose pixelformat with WGL_SAMPLES_ARB");
				return false;
			}
			
			if(!SetPixelFormat(m_DeviceContext, pixelformat, &pfd)) {
				KYRA_LOG_ERROR(GLContextWGL::create, "Failed to set pixelformat ( " << GetLastError() << " )");
				return false;
			}
			
			int attribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 2,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
			};
			
			m_RenderContext = wglCreateContextAttribsARB(m_DeviceContext, 0, attribs);
			wglMakeCurrent(m_DeviceContext, m_RenderContext);
			
			KYRA_LOG_INFO(GLContextWGL::create, "OpenGL Version: " << glGetString(GL_VERSION));
			KYRA_LOG_INFO(GLContextWGL::create, "OpenGL Vendor: " << glGetString(GL_VENDOR));
						
			wglDeleteContext(temporaryRenderContext);
			DeleteDC(temporaryDC);
				
			return true;
		}
		
		virtual void swapBuffers() final {
			SwapBuffers(m_DeviceContext);
		}
		
	};
	
	using GLContext = GLContextWGL;
}

#endif