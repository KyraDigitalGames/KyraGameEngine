#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_HPP

#include <Windows.h>
#include <gl/GL.h>
#include <cstdlib>

using GLchar = char;
using GLintptr = int*;
using GLsizeiptr = unsigned long long;

static constexpr unsigned int GL_FRAGMENT_SHADER = 0x8B30;
static constexpr unsigned int GL_VERTEX_SHADER = 0x8B31;
static constexpr unsigned int GL_COMPILE_STATUS = 0x8B81;
static constexpr unsigned int GL_LINK_STATUS = 0x8B82;
static constexpr unsigned int GL_INFO_LOG_LENGTH = 0x8B84;

static constexpr unsigned int GL_ARRAY_BUFFER = 0x8892;
static constexpr unsigned int GL_ELEMENT_ARRAY_BUFFER = 0x8893;
static constexpr unsigned int GL_STREAM_DRAW = 0x88E0;
static constexpr unsigned int GL_STREAM_READ = 0x88E1;
static constexpr unsigned int GL_STREAM_COPY = 0x88E2;
static constexpr unsigned int GL_STATIC_DRAW = 0x88E4;
static constexpr unsigned int GL_STATIC_READ = 0x88E5;
static constexpr unsigned int GL_STATIC_COPY = 0x88E6;
static constexpr unsigned int GL_DYNAMIC_DRAW = 0x88E8;
static constexpr unsigned int GL_DYNAMIC_READ = 0x88E9;
static constexpr unsigned int GL_DYNAMIC_COPY = 0x88EA;


typedef GLuint(*PFNGLCREATESHADERPROC)(GLenum type);
extern PFNGLCREATESHADERPROC glCreateShader;
typedef void (*PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
extern PFNGLSHADERSOURCEPROC glShaderSource;
typedef void (*PFNGLCOMPILESHADERPROC)(GLuint shader);
extern PFNGLCOMPILESHADERPROC glCompileShader;
typedef void (*PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint* params);
extern PFNGLGETSHADERIVPROC glGetShaderiv;
typedef void (*PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
typedef void (*PFNGLDELETESHADERPROC)(GLuint shader);
extern PFNGLDELETESHADERPROC glDeleteShader;

typedef GLuint(*PFNGLCREATEPROGRAMPROC)(void);
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
typedef void (*PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
extern PFNGLATTACHSHADERPROC glAttachShader;
typedef void (*PFNGLLINKPROGRAMPROC)(GLuint program);
extern PFNGLLINKPROGRAMPROC glLinkProgram;
typedef void (*PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint* params);
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
typedef void (*PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
typedef void (*PFNGLUSEPROGRAMPROC)(GLuint program);
extern PFNGLUSEPROGRAMPROC glUseProgram;
typedef void (*PFNGLDELETEPROGRAMPROC)(GLuint program);
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;

typedef void (*PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
extern PFNGLGENBUFFERSPROC glGenBuffers;
typedef void (*PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
extern PFNGLBINDBUFFERPROC glBindBuffer;
typedef void (*PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
extern PFNGLBUFFERDATAPROC glBufferData;
typedef void (*PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
typedef void (*PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint* buffers);
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

typedef void (*PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
typedef void (*PFNGLBINDVERTEXARRAYPROC)(GLuint array);
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
typedef void (*PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
typedef void (*PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
typedef void (*PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
typedef void (*PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint* arrays);
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;


namespace kyra {

	namespace gl {
		bool init();
	}

}

#endif