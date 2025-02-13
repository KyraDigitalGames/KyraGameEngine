#ifndef KYRAGAMEENGINE_RHI_ABSTRACTCOMMANDBUFFER_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTCOMMANDBUFFER_HPP

#include "AbstractRenderPipeline.hpp"
#include "AbstractVertexBuffer.hpp"

namespace kyra {
 
 class AbstractCommandBuffer {
    
    public:
    virtual ~AbstractCommandBuffer() = default;
    
    virtual void bindRenderPipeline(AbstractRenderPipeline* renderPipeline) = 0;
    virtual void bindVertexBuffer(AbstractVertexBuffer* vertexBuffer) = 0;
    virtual void draw(std::size_t offset, std::size_t count) = 0;
    virtual void submit() = 0;
    
 };
 
}

#endif