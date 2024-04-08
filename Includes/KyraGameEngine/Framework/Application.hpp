#ifndef KYRAGAMEENGINE_FRAMEWORK_APPLICATION_HPP
#define KYRAGAMEENGINE_FRAMEWORK_APPLICATION_HPP

#include <KyraGameEngine/Platform/WinAPI/WindowWinAPI.hpp>
#include <KyraGameEngine/Rendering/IRenderDevice.hpp>

namespace kyra {
	
	struct ApplicationSettings {
		WindowSettings windowSettings;
	};
	
	class Application {
		
		Window m_Window;
		
		// Virtual method for setting up application-specific settings
		// Subclasses should override this method to customize window settings
		[[nodiscard]] virtual bool onSetup(ApplicationSettings& settings) = 0;
		
		// Virtual method for initializing application
		// Subclasses should override this method to perform initialization tasks
		[[nodiscard]]  virtual bool onInit(IWindow& window, IRenderDevice& renderDevice) = 0;
	
		// Virtual method for updating application state
		// Subclasses should override this method to update application logic
		virtual void onUpdate() = 0;
		
		// Virtual method for rendering application content
		// Subclasses should override this method to render application graphics
		virtual void onDraw() = 0;
		
		public:
		
		// Virtual destructor to ensure proper destruction of derived classes
		virtual ~Application() = default;
		
		// Method to run the application
		// This method initializes the application, runs the main loop, and cleans up resources
		[[nodiscard]] int run();
		
	};
}

#endif