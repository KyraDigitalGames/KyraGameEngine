#include "CommandBufferOpenGL.hpp"

#include <Windows.h>
#include <gl/GL.h>

namespace kyra {

	void CommandBufferOpenGL::clear(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

}