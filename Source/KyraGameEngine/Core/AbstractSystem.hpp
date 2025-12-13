#ifndef KYRAGAMEENGINE_CORE_ABSTRACTSYSTEM_HPP
#define KYRAGAMEENGINE_CORE_ABSTRACTSYSTEM_HPP

namespace kyra {
  
  class AbstractSystem {
    
    public:
    virtual ~AbstractSystem() = default;

    virtual void update() = 0;
    
  };
  
}

#endif