#ifndef KYRAGAMEENGINE_RHI_HPP
#define KYRAGAMEENGINE_RHI_HPP

#ifdef KYRA_PLATFORM_WINDOWS
	#ifdef KYRA_RENDERER_OPENGL
		#include <KyraGameEngine/RHI/OpenGL/GraphicsContextOpenGL.hpp>
	#endif
#else
	#error "This renderer is not supported"
#endif

#endif