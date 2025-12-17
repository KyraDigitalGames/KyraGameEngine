#ifndef KYRAGAMEENGINE_SCRIPTING_SCRIPTCOMPONENTFACTORY_HPP
#define KYRAGAMEENGINE_SCRIPTING_SCRIPTCOMPONENTFACTORY_HPP

#include "ScriptComponentFactoryInterface.hpp"
#include "ScriptComponentInterface.hpp"

namespace kyra {
  
  template<class ScriptComponentType>
  class ScriptComponentFactory : public ScriptComponentFactoryInterface {

  public:

    std::unique_ptr<kyra::ScriptComponentInterface> create() final {
      return std::make_unique<ScriptComponentType>();
    }
  };

}

#endif