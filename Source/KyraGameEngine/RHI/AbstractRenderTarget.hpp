#ifndef KYRAGAMEENGINE_RHI_ABSTRACTRENDERTARGET_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTRENDERTARGET_HPP

namespace kyra {
  
  class AbstractRenderTarget {
    
    public:
    virtual ~AbstractRenderTarget() = default;
     
    virtual void bind() = 0;
    virtual void unbind() = 0;
  
  };
  
}

#endif