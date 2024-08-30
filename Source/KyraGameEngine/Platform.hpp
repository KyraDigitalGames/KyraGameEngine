#ifndef KYRAGAMEENGINE_PLATFORM_HPP
#define KYRAGAMEENGINE_PLATFORM_HPP

#ifdef KYRA_PLATFORM_WINDOWS
	#include <KyraGameEngine/Platform/Windows/WindowWinAPI.hpp>
	#include <KyraGameEngine/Platform/Windows/OpenGLContextWGL.hpp>
#else
	#error "This platform is not supported"
#endif

#endif