#include <KyraGameEngine/Framework/Application.hpp>
#include <KyraGameEngine/Log.hpp>

#ifdef KYRA_RENDERER_DX11
	#include <KyraGameEngine/Rendering/DirectX11/RenderDeviceDX11.hpp>
#else
	#include <KyraGameEngine/Rendering/OpenGL/RenderDeviceGL.hpp>
#endif

namespace kyra {
	
	int Application::run() {

			KYRA_LOG_INFO(Application::run, "Starting Kyra Game Engine...");

			KYRA_LOG_INFO(Application::run, "Get window settings...");
			ApplicationSettings settings;
			if(!onSetup(settings)) {
				return -1;
			}
			
			KYRA_LOG_INFO(Application::run, "Create window...");
			if(!m_Window.create(settings.windowSettings)) {
				return -2;
			}
			
			KYRA_LOG_INFO(Application::run, "Create renderer...");
			
			RenderDevice renderer;
			if(!renderer.create(m_Window)) {
				return -3;
			}
			
			KYRA_LOG_INFO(Application::run, "Initialize main game state...");
			if(!onInit(m_Window, renderer)) {
				return -4;
			}
				
			KYRA_LOG_INFO(Application::run, "Run main loop...");
			m_Window.show();
			while(m_Window.isOpen()) {
				m_Window.processEvents();
				onUpdate();
				renderer.beginDraw();
				onDraw();
				renderer.endDraw();
			}
			
			return 0;
	}

}