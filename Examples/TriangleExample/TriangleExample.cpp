#include <KyraGameEngine/Application/Game2D.hpp>
#include <KyraGameEngine/Asset/AssetManager.hpp>
#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Scene/2D/SceneRenderProcessor2D.hpp>
#include <KyraGameEngine/Renderer/RenderPassPresent.hpp>
#include <KyraGameEngine/Scene/2D/SceneSystem2D.hpp>

class TriangleExample : public kyra::Game2D {

public:

	bool onSetup(kyra::Game2DDescriptor& descriptor) final {
		descriptor.windowTitle = "Kyra Game Engine - Triangle Example";
		descriptor.windowWidth = 1000;
		descriptor.windowHeight = 800;
		return true;
	}

	bool onInit(kyra::SceneSystem2D* sceneSystem, kyra::Scene* scene) final {
		
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

};

KYRA_DEFINE_APPLICATION(TriangleExample)