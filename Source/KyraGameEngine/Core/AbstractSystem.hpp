#ifndef KYRAGAMEENGINE_CORE_ABSTRACTSYSTEM_HPP
#define KYRAGAMEENGINE_CORE_ABSTRACTSYSTEM_HPP

#include <KyraGameEngine/Core/Registry.hpp>

namespace kyra {

  
  class AbstractSystem {
  
    public:
    virtual ~AbstractSystem() = default;

    virtual void update(float deltaTime) = 0;
    
  };
  
}

#endif