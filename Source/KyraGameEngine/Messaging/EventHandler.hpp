#ifndef KYRAGAMEENGINE_MESSAGING_EVENTHANDLER_HPP
#define KYRAGAMEENGINE_MESSAGING_EVENTHANDLER_HPP

#include "EventBus.hpp"

namespace kyra {

	template<class T>
	class EventHandler : public T {

	public:
		EventHandler() {
			EventBus<T>::connect(this);
		}

		virtual ~EventHandler() {
			EventBus<T>::disconnect(this);
		}
	};

}

#endif