#ifndef KYRAGAMEENGINE_CORE_REGISTRY_HPP
#define KYRAGAMEENGINE_CORE_REGISTRY_HPP

#include <map>
#include <memory>

namespace kyra {
  template<class BaseType>
  class FactoryInterface {

  public:

    virtual std::shared_ptr<BaseType> create() = 0;

  };


  template<class BaseType, class ImplementationType>
  class Factory : public FactoryInterface<BaseType> {

  public:

    std::shared_ptr<BaseType> create() final {
      return std::make_shared<ImplementationType>();
    }

  };

  template<class BaseType>
  class Registry {

    std::map<std::string, std::unique_ptr<FactoryInterface<BaseType>>> m_Factories;


  public:

    template<class ImplementationType>
    void registerFactory(const std::string& name) {
      m_Factories[name] = std::make_unique<Factory<BaseType, ImplementationType>>();
    }

    std::shared_ptr<BaseType> create(const std::string& name) {
      auto it = m_Factories.find(name);
      if (it == m_Factories.end()) {
        return nullptr;
      }
      return it->second->create();
    }

  };
  
}

#endif