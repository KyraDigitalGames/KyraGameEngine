
#include <KyraGameEngine/Application/Application.hpp>
#include <KyraGameEngine/Renderer/Renderer.hpp>
#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Renderer/RenderPipeline.hpp>
#include <KyraGameEngine/Renderer/RenderPassPresent.hpp>
#include <KyraGameEngine/GameModule/GameModule.hpp>

#include <Windows.h>
#include <gl/GL.h>

class KyraPlayer : public kyra::Application {

	kyra::Window m_Window;
	kyra::Renderer m_Renderer;

	kyra::GameModule m_Module;

public:
	~KyraPlayer() {

	}


	bool onSetup() final {

		if (!m_Module.load("Game.dll")) {
			return false;
		}

		auto actor = m_Module.createActor("PlayerPadActor");
		if (!actor) {
			return false;
		}
		else {
			actor->update();
		}

		kyra::WindowDescriptor windowDescriptor;
		windowDescriptor.title = "Kyra Game Engine";
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

		kyra::RenderPipelineDescriptor renderPipelineDescriptor;
		renderPipelineDescriptor.commandBuffer = m_Renderer.acquireCommandBuffer();
		kyra::RenderPipeline renderPipeline;
		if (!renderPipeline.init(renderPipelineDescriptor)) {
			return false;
		}

		kyra::RenderPassPresentDescriptor renderPassPresentDescriptor;
		renderPassPresentDescriptor.swapchain = m_Renderer.acquireSwapchain();
		if (!renderPipeline.registerPass<kyra::RenderPassPresent>(renderPassPresentDescriptor)) {
			return false;
		}
		m_Renderer.setRenderPipeline(renderPipeline);


		return true;
	}


	virtual void onStart() final {

	}

	virtual void onUpdate() final {
		if (!m_Window.isOpen()) {
			quit();
		}
		m_Window.processEvents();
		m_Renderer.update();
	}

	virtual void onExit() final {

	}

};

KYRA_DEFINE_APPLICATION(KyraPlayer);
