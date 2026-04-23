#include "OpenGLContextWGL.hpp"

namespace kyra {

	OpenGLContext::Ptr OpenGLContext::create() {
		return std::make_unique<OpenGLContextWGL>();
	}

}