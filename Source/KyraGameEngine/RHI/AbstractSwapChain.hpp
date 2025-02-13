#ifndef KYRAGAMEENGINE_RHI_ABSTRACTSWAPCHAIN_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTSWAPCHAIN_HPP  

#include "AbstractRenderTarget.hpp"

#include <KyraGameEngine/Window/AbstractWindow.hpp>

namespace kyra {
  
  struct SwapChainDescriptor {
    AbstractWindow* window = nullptr;
  };
  
  
  class AbstractSwapChain : public AbstractRenderTarget {
    
    public:
    virtual ~AbstractSwapChain() = default;
    
    virtual bool init(const SwapChainDescriptor& descriptor) = 0;
  
  };
  
}

#endif