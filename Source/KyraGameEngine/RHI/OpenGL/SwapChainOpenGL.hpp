#ifndef KYRAGAMEENGINE_RHI_OPENGL_SWAPCHAINOPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_SWAPCHAINOPENGL_HPP

#ifdef KYRA_PLATFORM_WINDOWS
	#include "OpenGLContextWGL.hpp"
#else
	#error "This platform is not supported"
#endif

#include <KyraGameEngine/RHI/AbstractSwapChain.hpp>

namespace kyra {
	
	class SwapChainOpenGL : public AbstractSwapChain {
		
		OpenGLContext m_Context;
		
		public:
		
		[[nodiscard]] bool init(const SwapChainDescriptor& swapChainDescriptor ) final;
		void present() final;

	};
}

#endif