#ifndef PONG_PLAYERPADACTOR_HPP
#define PONG_PLAYERPADACTOR_HPP

#include <KyraGameEngine/Scripting/Actor.hpp>
#include <iostream>

class PlayerPadActor : public kyra::Actor {

public:

	void update() final {
		std::cout << "Hello World" << std::endl;
	}

};

KYRA_EXPORT_ACTOR(PlayerPadActor);

#endif