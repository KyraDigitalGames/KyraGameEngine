#ifndef KYRAGAMEENGINE_WINDOW_HPP
#define KYRAGAMEENGINE_WINDOW_HPP

#ifdef KYRA_PLATFORM_WINDOWS
	#include <KyraGameEngine/Platform/Windows/WindowWinAPI.hpp>
#else
	#error "This platform is not supported"
#endif

#endif