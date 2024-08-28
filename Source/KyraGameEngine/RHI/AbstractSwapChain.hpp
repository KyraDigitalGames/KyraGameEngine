#ifndef KYRAGAMEENGINE_RHI_ABSTRACTSWAPCHAIN_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTSWAPCHAIN_HPP

#include <KyraGameEngine/Platform/AbstractWindow.hpp>

namespace kyra {
	
	struct SwapChainDescriptor {
		AbstractWindow* window = nullptr;
	};
	
	class AbstractSwapChain {
		
		public:
		virtual ~AbstractSwapChain() = default;
		
		[[nodiscard]] virtual bool init(const SwapChainDescriptor& swapChainDescriptor ) = 0;
		virtual void present() = 0;
	};
	
}

#endif