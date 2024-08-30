#ifndef KYRAGAMEENGINE_CORE_CALLBACKINSTANCE_HPP
#define KYRAGAMEENGINE_CORE_CALLBACKINSTANCE_HPP

#include "CallbackInstanceOwner.hpp"
#include <functional>


namespace kyra {
	
	template<class... Arguments>
	class CallbackInstance {
		
		CallbackInstanceOwner<Arguments...>* m_Owner = nullptr;
		std::function<bool(Arguments...)> m_CallbackFunc;
		
		public:
		CallbackInstance(CallbackInstanceOwner<Arguments...>* owner, std::function<bool(Arguments...)> callback) : m_Owner(owner), m_CallbackFunc(callback) {

		}
		
		~CallbackInstance() {
			if(m_Owner) {
				m_Owner->disconnect(this);
			}
		}
				
		bool consumeEvent(Arguments... args) {
			return m_CallbackFunc(args...);
		}
		
	};
	
	template<>
	class CallbackInstance<void> {

		CallbackInstanceOwner<void>* m_Owner = nullptr;
		std::function<bool()> m_CallbackFunc;

		public:
		CallbackInstance(CallbackInstanceOwner<void>* owner, std::function<bool()> callback) : m_Owner(owner), m_CallbackFunc(callback) {

		}
		
		~CallbackInstance() {
			if(m_Owner) {
				m_Owner->disconnect(this);
			}
		}
				
		bool consumeEvent() {
			return m_CallbackFunc();
		}
		
	};
}

#endif