#ifndef KYRAGAMEENGINE_CORE_SYSTEMMANAGER_HPP
#define KYRAGAMEENGINE_CORE_SYSTEMMANAGER_HPP

#include "AbstractSystem.hpp"
#include <map>
#include <memory>
#include <typeinfo>

namespace kyra {
  
  class SystemManager  {
    
    std::map<std::size_t, std::unique_ptr<AbstractSystem>> m_SystemMap;
    
    public:
    
    template<class SystemType>
    SystemType* registerSystem() {
      auto id = typeid(SystemType).hash_code();
      m_SystemMap.emplace(id, std::make_unique<SystemType>());
      return static_cast<SystemType*>(m_SystemMap[id].get());
    }
    
    template<class SystemType>
    SystemType* getSystem() {
      auto id = typeid(SystemType).hash_code();
      auto it = m_SystemMap.find(id);
      if(it != m_SystemMap.end()) {
        return static_cast<SystemType*>(it->second.get());          
      }
      return nullptr;
    }

    std::size_t getSystemCount() const {
        return m_SystemMap.size();
    }

    void update(float deltaTime) {
        for (auto& system : m_SystemMap) {
            system.second->update(deltaTime);
        }
    }
    
  };
  
}

#endif