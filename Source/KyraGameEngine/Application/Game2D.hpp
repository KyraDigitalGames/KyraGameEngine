#ifndef KYRAGAMEENGINE_APPLICATION_GAME2D_HPP
#define KYRAGAMEENGINE_APPLICATION_GAME2D_HPP

#include "Application.hpp"

#include <KyraGameEngine/Application/Application.hpp>
#include <KyraGameEngine/Asset/AssetManager.hpp>
#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Scene/2D/SceneRenderProcessor2D.hpp>
#include <KyraGameEngine/Renderer/RenderPassPresent.hpp>
#include <KyraGameEngine/Scene/2D/SceneSystem2D.hpp>


namespace kyra {

	struct Game2DDescriptor {
		std::string windowTitle = "Kyra Game Engine";
		int windowWidth = 1280;
		int windowHeight = 720;
		bool windowFullscreen = false;
		kyra::RenderDeviceType renderDeviceType = kyra::RenderDeviceType::OpenGL;
	};

	class Game2D : public Application {

		virtual bool onSetup(Game2DDescriptor& descriptor) = 0;
		virtual bool onInit(kyra::SceneSystem2D* sceneSystem, kyra::Scene* scene) = 0;

	public:
		
		bool onSetup() final {

			Game2DDescriptor game2DDescriptor;
			if(!onSetup(game2DDescriptor)) {
				return false;
			}
						
			// CREATE THE WINDOW

			kyra::WindowDescriptor windowDescriptor;
			windowDescriptor.title = "Kyra Game Engine - Triangle Example";
			windowDescriptor.width = 1280;
			windowDescriptor.height = 720;
			windowDescriptor.fullscreen = false;

			kyra::Window* window = registerSystem<kyra::Window>();
			if (!window->init(windowDescriptor)) {
				return false;
			}

			// CREATE THE ASSET MANAGER

			kyra::AssetManager* assetManager = registerSystem<kyra::AssetManager>();


			// CREATE THE RENDERER

			kyra::RendererDescriptor rendererDescriptor;
			rendererDescriptor.type = kyra::RenderDeviceType::OpenGL;
			rendererDescriptor.assetManager = assetManager;
			rendererDescriptor.window = window;

			kyra::Renderer* renderer = registerSystem<kyra::Renderer>();
			if (!renderer->init(rendererDescriptor)) {
				return false;
			}
			renderer->registerRenderPassProcessorType<kyra::SceneRenderPassProcessor2D>("SceneRenderPassProcessor2D");

			// CREATE THE RENDER PIPELINE 

			kyra::RenderPassEntry renderPassEntry;
			renderPassEntry.name = kyra::RenderPassPresent::Id;
			renderPassEntry.processorName = "SceneRenderPassProcessor2D";

			kyra::RenderPipelineDescriptor renderPipelineDescriptor;
			renderPipelineDescriptor.systemManager = getSystemManager();
			renderPipelineDescriptor.renderer = renderer;
			renderPipelineDescriptor.m_RenderPasses.emplace_back(renderPassEntry);

			kyra::RenderPipeline* renderPipeline = renderer->createRenderPipeline("DefaultPipeline");
			if (!renderPipeline->init(renderPipelineDescriptor)) {
				return false;
			}

			// CREATE THE SCENE

			kyra::SceneSystem2D* sceneSystem = registerSystem<kyra::SceneSystem2D>();
			kyra::Scene* scene = sceneSystem->createScene("DefaultScene");
			scene->setRenderPipeline(renderPipeline);
			sceneSystem->setActiveScene(scene);
			if (!onInit(sceneSystem, scene)) {
				return false;
			}
			return true;
		}

		void onStart() final {

		}

		void onExit() final {

		}
	};
}


#endif