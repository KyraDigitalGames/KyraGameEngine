#ifndef KYRAGAMEENGINE_RHI_ABSTRACTSHADER_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTSHADER_HPP

#include <cstdint>

namespace kyra {
  
  enum class ShaderStage {
    Vertex,
    Fragment
  };
  
  struct ShaderDescriptor {
    const char* code = nullptr;
    std::size_t size = 0;
    ShaderStage stage = ShaderStage::Vertex;
  };
  
  class AbstractShader {
    
    public:
    virtual ~AbstractShader() = default;
    
    virtual bool init(const ShaderDescriptor& shaderDescriptor) = 0;
    virtual std::size_t getId() const = 0;
    
  };
  
}

#endif