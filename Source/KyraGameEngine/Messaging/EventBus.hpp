#ifndef KYRAGAMEENGINE_MESSAGING_EVENTBUS_HPP
#define KYRAGAMEENGINE_MESSAGING_EVENTBUS_HPP

#include <vector>

namespace kyra {

	template<class T>
	class EventBus {

		static EventBus<T>& getInstance() {
			static EventBus<T> instance;
			return instance;
		}

		std::vector<T*> m_Listeners;

	public:

		static void connect(T* listener) {
			getInstance().m_Listeners.push_back(listener);
		}

		static void disconnect(T* listener) {
			EventBus<T>& instance = getInstance();
			auto it = std::find(instance.m_Listeners.begin(), instance.m_Listeners.end(), listener);
			if (it != instance.m_Listeners.end()) {
				instance.m_Listeners.erase(it);
			}
		}

		template<class Function, class ... Args>
		static void dispatch(Function func, Args... args) {
			for (auto& listener : getInstance().m_Listeners) {
				if ((listener->*func)(args...)) {
					return;
				}
			}
		}

	};

}

#endif