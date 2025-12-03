#ifndef KYRAGAMEENGINE_SCRIPTING_ACTOR_HPP
#define KYRAGAMEENGINE_SCRIPTING_ACTOR_HPP

namespace kyra {

	class Actor {

	public:
		virtual ~Actor() = default;

		virtual void update() = 0;

	};

}

#define KYRA_EXPORT_ACTOR(ActorType)

#endif