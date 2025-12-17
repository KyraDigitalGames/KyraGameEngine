#ifndef KYRAGAMEENGINE_SCRIPTING_SCRIPTSYSTEM_HPP
#define KYRAGAMEENGINE_SCRIPTING_SCRIPTSYSTEM_HPP

#include <KyraGameEngine/Core/System.hpp>
#include <map>
#include <vector>
#include <memory>

#include "ScriptComponentInterface.hpp"

namespace kyra {
  
  class ScriptSystem : public System {

    std::map<std::size_t, std::unique_ptr<ScriptComponentFactoryInterface>> m_Factories;
    std::vector<std::unique_ptr<ScriptComponentInterface>> m_Components;

  public:

    template<class ScriptComponentType>
    void registerScriptComponentType() {
      auto id = typeid(ScriptComponentType).hash_code();
      m_Factories.emplace(id, std::make_unique<ScriptComponentFactory<ScriptComponentType>>());
    }

    template<class ScriptComponentType> 
    ScriptComponentType* create() {
      m_Components.emplace_back(m_Factories[typeid(ScriptComponentType).hash_code()]->create());
      return static_cast<ScriptComponentType*>(m_Components.back().get());
    }

    void update(float deltaTime) {
      for (auto& component : m_Components) {
        component->update(deltaTime);
      }
    }

  };

  
}


#endif