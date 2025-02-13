#ifndef KYRAGAMEENGINE_RHI_ABSTRACTRENDERDEVICE_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTRENDERDEVICE_HPP

#include "AbstractRenderPass.hpp"
#include "AbstractCommandBuffer.hpp"
#include "AbstractCopyPass.hpp"
#include "AbstractRenderPipeline.hpp"
#include "AbstractShader.hpp"
#include "AbstractTransferBuffer.hpp"
#include "AbstractVertexBuffer.hpp"


#include <KyraGameEngine/Window/AbstractWindow.hpp>

namespace kyra {
  
  struct RenderDeviceDescriptor {
    AbstractWindow* window = nullptr;
  };
  
  class AbstractRenderDevice {
    
    public:
    virtual ~AbstractRenderDevice() = default;
    
    virtual bool init(const RenderDeviceDescriptor& descriptor) = 0;
    virtual AbstractSwapChain* getSwapChain() = 0;
    virtual AbstractCommandBuffer* getCommandBuffer() = 0;
    virtual std::unique_ptr<AbstractRenderPass> createRenderPass() = 0;
    virtual std::unique_ptr<AbstractCopyPass> createCopyPass() = 0;
    virtual std::unique_ptr<AbstractRenderPipeline> createRenderPipeline() = 0;
    virtual std::unique_ptr<AbstractShader> createShader() = 0;
    virtual std::unique_ptr<AbstractTransferBuffer> createTransferBuffer() = 0;
    virtual std::unique_ptr<AbstractVertexBuffer> createVertexBuffer() = 0;
      
  };
}

#endif