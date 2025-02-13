#ifndef KYRAGAMEENGINE_RHI_ABSTRACTVERTEXBUFFER_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTVERTEXBUFFER_HPP

namespace kyra {
  
  struct VertexBufferDescriptor {
    std::size_t size = 0;
  }; 
  
  class AbstractVertexBuffer {
    
    public:
    virtual ~AbstractVertexBuffer() = default;
    
    virtual bool init(const VertexBufferDescriptor& descriptor) = 0;
    virtual std::size_t getSize() const = 0;
  };
  
}

#endif