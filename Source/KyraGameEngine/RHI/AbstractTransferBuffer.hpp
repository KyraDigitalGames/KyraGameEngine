#ifndef KYRAGAMEENGINE_RHI_ABSTRACTTRANSFERBUFFER_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTTRANSFERBUFFER_HPP

namespace kyra {
  
  enum class TransferBufferUsage {
    Upload
  };

  struct TransferBufferDescriptor {
    TransferBufferUsage usage;
    std::size_t size = 0;
  };
  
  class AbstractTransferBuffer {
    
    public:
    virtual ~AbstractTransferBuffer() = default;
    
    virtual bool init(const TransferBufferDescriptor& descriptor) = 0;
    virtual uint8_t* map() = 0;
    virtual void unmap() = 0;
    virtual std::size_t getSize() = 0;
    virtual uint8_t* getData() = 0;
    
    
  };
}

#endif