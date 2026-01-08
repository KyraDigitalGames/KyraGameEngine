
#include "Application.hpp"
#include <KyraGameEngine/Window/WindowImplementation.hpp>
#include <chrono>

namespace kyra {

	Application::~Application() {
		Logger::get().stop();
	}

	void Application::update() {
		static auto previousTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		m_SystemManager.update(deltaTime.count());
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

		WindowEvents::onClose.connect(this, [&]() {
			m_IsRunning = false;
			return true;
		});


		onStart();
		
		if (m_SystemManager.getSystemCount() > 0) {
			m_IsRunning = true;
		}

		while (m_IsRunning) {
			update();
		}

		onExit();
		
		KYRA_LOG_INFO("Finished");
		return 0;
	}

	void Application::quit() {
		m_IsRunning = false;
	}

}