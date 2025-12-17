#ifndef KYRAGAMEENGINE_SCRIPTING_SCRIPTCOMPONENTINTERFACE_HPP
#define KYRAGAMEENGINE_SCRIPTING_SCRIPTCOMPONENTINTERFACE_HPP

#include <KyraGameEngine/Scene/Component.hpp>

namespace kyra {
  
 class ScriptComponentInterface : public Component {

  public:
	virtual ~ScriptComponentInterface() = default;
	virtual void update(float deltaTime) = 0;

};

  
}

#endif