#ifndef KYRAGAMEENGINE_CORE_CALLBACKINSTANCEOWNER_HPP
#define KYRAGAMEENGINE_CORE_CALLBACKINSTANCEOWNER_HPP


namespace kyra {

	template<class... Arguments>
	class CallbackInstance;
	
	template<class... Arguments>
	class CallbackInstanceOwner {
		
		public:
		virtual ~CallbackInstanceOwner() = default;
		
		virtual void disconnect(CallbackInstance<Arguments...>* owner) = 0;
		
	};

}

#endif