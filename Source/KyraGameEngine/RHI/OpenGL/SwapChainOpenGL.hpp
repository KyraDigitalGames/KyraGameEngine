#ifndef KYRAGAMEENGINE_RHI_OPENGL_SWAPCHAINOPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_SWAPCHAINOPENGL_HPP

#include <KyraGameEngine/Platform.hpp>
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