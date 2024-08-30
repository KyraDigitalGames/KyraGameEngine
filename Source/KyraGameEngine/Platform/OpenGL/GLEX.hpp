#ifndef KYRAGAMEENGINE_RHI_OPENGL_GLEX_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_GLEX_HPP

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wgl.h>
#include <GL/wglext.h>

// VERTEX BUFFER FUNCTIONS
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

// SHADER FUNCTIONS
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

// SHADER PROGRAM FUNCTIONS
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

// VERTEX ARRAY OBJECT FUNCTIONS
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;


namespace glex {
	
	/// Loads the OpenGL extension functions
	/// Returns false if a function could not get loaded
	template<class LoadFunc>
	[[nodiscard]] bool init(LoadFunc function) {
		
		// LOAD VERTEX BUFFER FUNCTIONS
		
		glGenBuffers = (PFNGLGENBUFFERSPROC)function("glGenBuffers");
		if(!glGenBuffers) {
			return false;
		}
		glBindBuffer = (PFNGLBINDBUFFERPROC)function("glBindBuffer");
		if(!glBindBuffer) {
			return false;
		}
		glBufferData = (PFNGLBUFFERDATAPROC)function("glBufferData");
		if(!glBufferData) {
			return false;
		}
		glBufferSubData = (PFNGLBUFFERSUBDATAPROC)function("glBufferSubData");
		if(!glBufferSubData) {
			return false;
		}
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)function("glDeleteBuffers");
		if(!glDeleteBuffers) {
			return false;
		}
		
		// LOAD SHADER FUNCTIONS
		
		glCreateShader = (PFNGLCREATESHADERPROC)function("glCreateShader");
		if(!glCreateShader) {
			return false;
		}
		glShaderSource = (PFNGLSHADERSOURCEPROC)function("glShaderSource");
		if(!glShaderSource) {
			return false;
		}
		glCompileShader = (PFNGLCOMPILESHADERPROC)function("glCompileShader");
		if(!glCompileShader) {
			return false;
		}
		glGetShaderiv = (PFNGLGETSHADERIVPROC)function("glGetShaderiv");
		if(!glGetShaderiv) {
			return false;
		}
		glDeleteShader = (PFNGLDELETESHADERPROC)function("glDeleteShader");
		if(!glDeleteShader) {
			return false;
		}
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)function("glGetShaderInfoLog");
		if(!glGetShaderInfoLog) {
			return false;
		}
		
		// LOAD SHADER PROGRAM FUNCTIONS
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)function("glCreateProgram");
		if(!glCreateProgram) {
			return false;
		}
		glAttachShader = (PFNGLATTACHSHADERPROC)function("glAttachShader");
		if(!glAttachShader) {
			return false;
		}
		glLinkProgram = (PFNGLLINKPROGRAMPROC)function("glLinkProgram");
		if(!glLinkProgram) {
			return false;
		}
		glUseProgram = (PFNGLUSEPROGRAMPROC)function("glUseProgram");
		if(!glUseProgram) {
			return false;
		}
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)function("glDeleteProgram");
		if(!glDeleteProgram) {
			return false;
		}
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)function("glGetProgramiv");
		if(!glGetProgramiv) {
			return false;
		}
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)function("glGetProgramInfoLog");
		if(!glGetProgramInfoLog) {
			return false;
		}
		
		// VERTEX ARRAY OBJECT FUNCTIONS
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)function("glGenVertexArrays");
		if(!glGenVertexArrays) {
			return false;
		}
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)function("glBindVertexArray");
		if(!glBindVertexArray) {
			return false;
		}
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)function("glVertexAttribPointer");
		if(!glVertexAttribPointer) {
			return false;
		}
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)function("glEnableVertexAttribArray");
		if(!glEnableVertexAttribArray) {
			return false;
		}
		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)function("glDisableVertexAttribArray");
		if(!glDisableVertexAttribArray) {
			return false;
		}
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)function("glDeleteVertexArrays");
		if(!glDeleteVertexArrays) {
			return false;
		}
		return true;
	}
	
}

#include <iostream>
#define GLEX_CHECK(x) (x); { GLenum err = glGetError(); if(err != GL_NO_ERROR) {std::cout << "[GL_ERROR] " << #x << " " << __FILE__ << " " << __LINE__ << std::endl;}};

#endif