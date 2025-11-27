
#include "Application.hpp"

namespace kyra {

	Application::~Application() {
		Logger::get().stop();
	}

	int Application::run(int argc, char** argv)
	{
		//Initialise Logging System
		LoggerDescriptor loggerDescriptor;
		loggerDescriptor.bufferSize = 32;
		loggerDescriptor.file = "Pong.txt";
		loggerDescriptor.append = false;
		Logger::get().start(loggerDescriptor);

		KYRA_LOG_INFO("Starting Kyra Game Engine");
		
		if (!onSetup()) {
			return -1;
		}

		m_IsRunning = true;
		onStart();
		while (m_IsRunning) {
			onUpdate();
		}

		onExit();
		
		KYRA_LOG_INFO("Finished");
		return 0;
	}

	void Application::quit() {
		m_IsRunning = false;
	}

}