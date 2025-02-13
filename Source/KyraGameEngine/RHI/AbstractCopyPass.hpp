#ifndef KYRAGAMEENGINE_RHI_ABSTRACTCOPYPASS_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTCOPYPASS_HPP

#include "AbstractCommandBuffer.hpp"
#include "AbstractTransferBuffer.hpp"
#include "AbstractVertexBuffer.hpp"

namespace kyra {
  
  class AbstractCopyPass {
    
    public:
    
    virtual void begin() = 0;
    virtual void upload(AbstractCommandBuffer* commandbuffer, AbstractTransferBuffer* source, AbstractVertexBuffer* target) = 0;
    virtual void end() = 0;
    
  };
  
}

#endif