
#include <KyraGameEngine/Application/Application.hpp>
#include <KyraGameEngine/Renderer/Renderer.hpp>
#include <KyraGameEngine/Window/Window.hpp>

#include <Windows.h>
#include <gl/GL.h>

class Pong : public kyra::Application {

	kyra::Window m_Window;
	kyra::Renderer m_Renderer;

public:

	bool onSetup() final {
		
		kyra::WindowDescriptor windowDescriptor;
		windowDescriptor.title = "Pong";
		windowDescriptor.width = 1280;
		windowDescriptor.height = 720;
		if (!m_Window.init(windowDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialise window");
			return false;
		}

		kyra::RendererDescriptor rendererDescriptor;
		rendererDescriptor.type = kyra::RenderDeviceType::OpenGL;
		rendererDescriptor.window = &m_Window;
		if (!m_Renderer.init(rendererDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialise renderer");
			return false;
		}

		return true;
	}


	virtual void onStart() final {
	
	}
	
	virtual void onUpdate() final {
		if (!m_Window.isOpen()) {
			quit();
		}
		m_Window.processEvents();
		
		kyra::Swapchain* swapchain = m_Renderer.acquireSwapchain();
		kyra::CommandBuffer* commandBuffer = m_Renderer.acquireCommandBuffer();
		commandBuffer->clear(1, 0, 0, 0);
		/*glBegin(GL_TRIANGLES);
		glColor3f(0, 1, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 1);
		glVertex2f(1, 1);
		glEnd();*/
		swapchain->swap();
	}
	
	virtual void onExit() final {

	}

};

KYRA_DEFINE_APPLICATION(Pong);
