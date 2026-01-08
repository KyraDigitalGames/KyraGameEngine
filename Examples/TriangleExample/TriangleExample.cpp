#include <KyraGameEngine/Application/Application.hpp>
#include <KyraGameEngine/Asset/AssetManager.hpp>
#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Scene/2D/SceneRenderProcessor2D.hpp>
#include <KyraGameEngine/Renderer/RenderPassPresent.hpp>
#include <KyraGameEngine/Scene/2D/SceneSystem2D.hpp>

class TriangleExample : public kyra::Application {

public:

	bool onSetup() final {

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

		std::vector<float> vertices = {
			640,100,0,0,
		    320,500,0,0,
			960,500,0,0
		};

		auto* triangleNode = scene->createNode("Triangle");
		triangleNode->addComponent(sceneSystem->createMeshComponent());
		triangleNode->addComponent(sceneSystem->createTransformComponent());
		auto* component = triangleNode->getComponent<kyra::MeshComponent2D>();
		component->setData(vertices);

		kyra::WindowEvents::onKeyUp.connect(this, [&](kyra::Key key) {
			if (key == kyra::Key::Escape) {
				quit();
				return true;
			}
			return false;
		});


		return true;
	}

	void onStart() final {

	}

	void onExit() final {

	}

};

KYRA_DEFINE_APPLICATION(TriangleExample)