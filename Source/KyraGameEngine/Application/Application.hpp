#ifndef KYRAGAMEENGINE_APPLICATION_APPLICATION_HPP
#define KYRAGAMEENGINE_APPLICATION_APPLICATION_HPP

#include <KyraGameEngine/Log/Logger.hpp>
#include <KyraGameEngine/Core/SystemManager.hpp>

namespace kyra {

	class Application {

		bool m_IsRunning = false;
		SystemManager m_SystemManager;

		public:
			virtual ~Application();

		template<class SystemType>
		SystemType* registerSystem() {
		  return m_SystemManager.registerSystem<SystemType>();
		}

	
		SystemManager* getSystemManager() {
			return &m_SystemManager;
		}


		virtual bool onSetup() = 0;
		virtual void onStart() = 0;
		virtual void onExit() = 0;

		void update();
		int run(int argc, char** argv);
		void quit();
	};

}

#define KYRA_DEFINE_APPLICATION(AppType) int main(int argc, char** argv) {\
	return AppType().run(argc, argv);\
}

#endif