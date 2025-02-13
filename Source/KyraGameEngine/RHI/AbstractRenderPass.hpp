#ifndef KYRAGAMEENGINE_RHI_ABSTRACTRENDERPASS_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTRENDERPASS_HPP

#include "AbstractRenderTarget.hpp"
#include "AbstractCommandBuffer.hpp"

namespace kyra {
  
  struct RenderPassDescriptor {
    AbstractRenderTarget* target;
    AbstractCommandBuffer* commandBuffer;
  };
  
  class AbstractRenderPass {
    
    public:
    virtual ~AbstractRenderPass() = default;
    
    virtual bool init(const RenderPassDescriptor& renderPassDescriptor) = 0;
    virtual void begin() = 0;
    virtual void end() = 0;
    
  };
  
}

#endif