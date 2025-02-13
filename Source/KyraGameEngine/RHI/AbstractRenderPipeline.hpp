#ifndef KYRAGAMEENGINE_RHI_ABSTRACTRENDERPIPELINE_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTRENDERPIPELINE_HPP

#include "AbstractShader.hpp"

namespace kyra {
  
  struct RenderPipelineDescriptor {
      AbstractShader* vertexShader;
      AbstractShader* fragmentShader;
  };
  
  class AbstractRenderPipeline {
    
    public:
    virtual ~AbstractRenderPipeline() = default;
    
    virtual bool init(const RenderPipelineDescriptor& descriptor) = 0;
    
  };
  
}

#endif