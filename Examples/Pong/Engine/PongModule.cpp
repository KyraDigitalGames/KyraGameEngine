#include <KyraGameEngine/GameModule/GameModule.hpp>
#include "PlayerPadActor.hpp"
#include "SimpleRenderPassProcessor.hpp"

KYRA_GAMEMODULE_START(Pong)
KYRA_REGISTER_ACTOR(PlayerPadActor)
KYRA_REGISTER_RENDERPASSPROCESSOR(SimpleRenderPassProcessor)
KYRA_GAMEMMODULE_END
