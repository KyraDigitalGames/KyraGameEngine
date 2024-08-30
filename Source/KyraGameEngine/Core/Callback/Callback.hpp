#ifndef KYRAGAMEENGINE_CORE_CALLBACK_CALLBACK_HPP
#define KYRAGAMEENGINE_CORE_CALLBACK_CALLBACK_HPP

#include "CallbackInstanceOwner.hpp"
#include "CallbackInstance.hpp"

#include <vector>
#include <memory>

namespace kyra {
	
	template<class... Arguments>
	class Callback : public CallbackInstanceOwner<Arguments...> {
		
		std::vector<CallbackInstance<Arguments...>*> m_RegisteredCallbacks;
		
		public:
		
		std::unique_ptr<CallbackInstance<Arguments...>> connect(  std::function<bool(Arguments...)> func ) {
			auto instance = std::make_unique<CallbackInstance<Arguments...>>(this, func);
			m_RegisteredCallbacks.push_back(instance.get());
			return instance;
		}
		
		
		void disconnect(CallbackInstance<Arguments...>* instance ) {
			auto it = std::find(m_RegisteredCallbacks.begin(), m_RegisteredCallbacks.end(), instance);
			if(it != m_RegisteredCallbacks.end()) {
				m_RegisteredCallbacks.erase(it);
			}
		}
		
		void dispatch(Arguments... args) {
			for(auto& entry : m_RegisteredCallbacks) {
				entry->consumeEvent(args...);
			}
		}
		
	
	};
	
	template<>
	class Callback<void> : public CallbackInstanceOwner<void> {
		
		std::vector<CallbackInstance<void>*> m_RegisteredCallbacks;
		
		public:
		
		std::unique_ptr<CallbackInstance<void>> connect(  std::function<bool(void)> func ) {
			auto instance = std::make_unique<CallbackInstance<void>>(this, func);
			m_RegisteredCallbacks.push_back(instance.get());
			return instance;
		}
		
		
		void disconnect(CallbackInstance<void>* instance ) {
			auto it = std::find(m_RegisteredCallbacks.begin(), m_RegisteredCallbacks.end(), instance);
			if(it != m_RegisteredCallbacks.end()) {
				m_RegisteredCallbacks.erase(it);
			}
		}
		
		void dispatch(void) {
			for(auto& entry : m_RegisteredCallbacks) {
				entry->consumeEvent();
			}
		}
		
	
	};
}

#endif