#ifndef KYRAGAMEENGINE_WINDOW_WINDOWEVENT_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOWEVENT_HPP

#include <KyraGameEngine/Messaging/EventHandler.hpp>

namespace kyra {

	class WindowEvent {

	public:
		virtual ~WindowEvent() = default;

		using Handler = EventHandler<WindowEvent>;


		virtual bool onClose() = 0;

	};

	using WindowEventBus = EventBus<WindowEvent>;

}

#endif