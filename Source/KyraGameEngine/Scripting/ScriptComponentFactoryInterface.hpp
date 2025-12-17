#ifndef KYRAGAMEENGINE_SCRIPTING_SCRIPTCOMPONENTFACTORYINTERFACE_HPP
#define KYRAGAMEENGINE_SCRIPTING_SCRIPTCOMPONENTFACTORYINTERFACE_HPP

#include "ScriptComponentInterface.hpp"
#include <memory>

namespace kyra {
  
  class ScriptComponentFactoryInterface {

  public:
    virtual ~ScriptComponentFactoryInterface() = default;

    virtual std::unique_ptr<kyra::ScriptComponentInterface> create() = 0;

  };

}

#endif