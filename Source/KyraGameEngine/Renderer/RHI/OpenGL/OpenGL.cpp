#include "OpenGL.hpp"

PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;

PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;

PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;

namespace kyra {
	
	namespace gl {
		bool init() {

			glCreateShader = (PFNGLCREATESHADERPROC)(wglGetProcAddress("glCreateShader"));
			glShaderSource = (PFNGLSHADERSOURCEPROC)(wglGetProcAddress("glShaderSource"));
			glCompileShader = (PFNGLCOMPILESHADERPROC)(wglGetProcAddress("glCompileShader"));
			glGetShaderiv = (PFNGLGETSHADERIVPROC)(wglGetProcAddress("glGetShaderiv"));
			glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)(wglGetProcAddress("glGetShaderInfoLog"));
			glDeleteShader = (PFNGLDELETESHADERPROC)(wglGetProcAddress("glDeleteShader"));

			glCreateProgram = (PFNGLCREATEPROGRAMPROC)(wglGetProcAddress("glCreateProgram"));
			glAttachShader = (PFNGLATTACHSHADERPROC)(wglGetProcAddress("glAttachShader"));
			glLinkProgram = (PFNGLLINKPROGRAMPROC)(wglGetProcAddress("glLinkProgram"));
			glGetProgramiv = (PFNGLGETPROGRAMIVPROC)(wglGetProcAddress("glGetProgramiv"));
			glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)(wglGetProcAddress("glGetProgramInfoLog"));
			glUseProgram = (PFNGLUSEPROGRAMPROC)(wglGetProcAddress("glUseProgram"));
			glDeleteProgram = (PFNGLDELETEPROGRAMPROC)(wglGetProcAddress("glDeleteProgram"));

			glGenBuffers = (PFNGLGENBUFFERSPROC)(wglGetProcAddress("glGenBuffers"));
			glBindBuffer = (PFNGLBINDBUFFERPROC)(wglGetProcAddress("glBindBuffer"));
			glBufferData = (PFNGLBUFFERDATAPROC)(wglGetProcAddress("glBufferData"));
			glBufferSubData = (PFNGLBUFFERSUBDATAPROC)(wglGetProcAddress("glBufferSubData"));
			glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)(wglGetProcAddress("glDeleteBuffers"));

			glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)(wglGetProcAddress("glGenVertexArrays"));
			glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)(wglGetProcAddress("glBindVertexArray"));
			glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)(wglGetProcAddress("glVertexAttribPointer"));
			glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)(wglGetProcAddress("glDisableVertexAttribArray"));
			glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)(wglGetProcAddress("glEnableVertexAttribArray"));
			glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)(wglGetProcAddress("glDeleteVertexArrays"));

			return true;
		}
	}

}