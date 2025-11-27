#ifndef KYRAGAMEENGINE_APPLICATION_APPLICATION_HPP
#define KYRAGAMEENGINE_APPLICATION_APPLICATION_HPP

#include <KyraGameEngine/Log/Logger.hpp>

namespace kyra {

	class Application {

		bool m_IsRunning = false;

	public:
		virtual ~Application();

		virtual bool onSetup() = 0;
		virtual void onStart() = 0;
		virtual void onUpdate() = 0;
		virtual void onExit() = 0;

		int run(int argc, char** argv);
		void quit();
	};

}

#define KYRA_DEFINE_APPLICATION(AppType) int main(int argc, char** argv) {\
	return AppType().run(argc, argv);\
}

#endif