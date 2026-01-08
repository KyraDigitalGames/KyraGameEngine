
#include <KyraGameEngine/Application/Application.hpp>
#include <KyraGameEngine/Renderer/Renderer.hpp>
#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Renderer/RenderPipeline.hpp>
#include <KyraGameEngine/Renderer/RenderPassPresent.hpp>
#include <KyraGameEngine/Renderer/RenderPassProcessor.hpp>
#include <KyraGameEngine/Math/Matrix4.hpp>
#include <KyraGameEngine/Math/Vector2.hpp>
#include <KyraGameEngine/Input/InputManager.hpp>
#include <KyraGameEngine/Input/Keyboard.hpp>
#include <KyraGameEngine/Scripting/Actor.hpp>
#include <KyraGameEngine/Core/AbstractSystem.hpp>
#include <KyraGameEngine/Core/System.hpp>
#include <KyraGameEngine/Scripting/ScriptComponentFactory.hpp>
#include <KyraGameEngine/Scene/Node.hpp>
#include <KyraGameEngine/Scripting/ScriptSystem.hpp>
#include <KyraGameEngine/Scripting/ScriptComponent.hpp>
#include <KyraGameEngine/Scene/Scene.hpp>
#include <KyraGameEngine/Image/ImageManager.hpp>
#include <KyraGameEngine/Scene/2D/SceneSystem2D.hpp>
#include <KyraGameEngine/Scene/2D/SceneRenderProcessor2D.hpp>
#include <KyraGameEngine/Audio/AudioController.hpp>
#include <KyraGameEngine/Asset/AssetManager.hpp>


class PhysicsComponent2D : public kyra::Component {
	
	kyra::Vector2<float> m_Velocity;

	public:
	
	void addForce(const kyra::Vector2<float>& vec) {
		m_Velocity = vec;
	}

	const kyra::Vector2<float>& getVelocity() const {
		return m_Velocity;
	}

	virtual std::size_t getHash() const {
		return typeid(PhysicsComponent2D).hash_code();
	}

	kyra::Signal<PhysicsComponent2D*, PhysicsComponent2D*> onCollision;

};

class PhysicsSystem2D : public kyra::System {

	std::vector<std::unique_ptr<PhysicsComponent2D>> m_Components;


	bool checkAABBOverlap(const kyra::Vector2<float>& posA, const kyra::Vector2<float>& sizeA,
		const kyra::Vector2<float>& posB, const kyra::Vector2<float>& sizeB) {
		return (posA.getX() < posB.getX() + sizeB.getX() &&
			posA.getX() + sizeA.getX() > posB.getX() &&
			posA.getY() < posB.getY() + sizeB.getY() &&
			posA.getY() + sizeA.getY() > posB.getY());
	}


public:
	void update(float deltaTime) final {
		for (auto& component : m_Components) {
			kyra::TransformComponent2D* transform = component->getNode()->getComponent<kyra::TransformComponent2D>();
			kyra::Vector2<float> position = transform->getPosition();
			auto velocity = component->getVelocity();
			position += kyra::Vector2<float>(velocity.getX() * deltaTime, velocity.getY() * deltaTime);
			transform->setPosition(position);
			transform->markWorldDirty();
		}
		for (auto& component : m_Components) {
			kyra::TransformComponent2D* transformA = component->getNode()->getComponent<kyra::TransformComponent2D>();
			kyra::Vector2<float> positionA = transformA->getPosition();
			kyra::Vector2<float> sizeA = transformA->getSize();
			for (auto& otherComponent : m_Components) {
				if (component.get() == otherComponent.get()) {
					continue;
				}
				kyra::TransformComponent2D* transformB = otherComponent->getNode()->getComponent<kyra::TransformComponent2D>();
				kyra::Vector2<float> positionB = transformB->getPosition();
				kyra::Vector2<float> sizeB = transformB->getSize();
				if (checkAABBOverlap(positionA, sizeA, positionB, sizeB)) {
					component->onCollision.dispatch(component.get(), otherComponent.get());
				}
			}
		}
	}

	PhysicsComponent2D* create() {
		m_Components.emplace_back(std::make_unique<PhysicsComponent2D>());
		return m_Components.back().get();
	}

};


class PlayerPadScriptComponent : public kyra::ScriptComponent {

public:

	void update(float deltaTime) final {
	kyra::Node* node = getNode();
		if(node->hasComponent<kyra::TransformComponent2D>()) {
			kyra::TransformComponent2D* transform = node->getComponent<kyra::TransformComponent2D>();
			kyra::Vector2<float> position = transform->getPosition();
			if(kyra::Keyboard::isPressed(kyra::Key::Left)) {
				position = kyra::Vector2<float>(position.getX() - (500*deltaTime), 0);
			}
			if(kyra::Keyboard::isPressed(kyra::Key::Right)) {
				position = kyra::Vector2<float>(position.getX() + (500*deltaTime), 0);
			}
			
			transform->setPosition(position);
			transform->markWorldDirty();
		}
		if (node->hasComponent<kyra::AudioComponent>()) {
			if (kyra::Keyboard::isPressed(kyra::Key::Up)) {
				node->getComponent<kyra::AudioComponent>()->play();
			}
		}
	}

	virtual std::size_t getHash() const {
		return typeid(PlayerPadScriptComponent).hash_code();
	}

};

class AIPadScriptComponent : public kyra::ScriptComponent {
	
	public:
	
	void update(float deltaTime) final {
		// AI logic here
		auto* ball = getScene()->getNode("BallNode");
		if (ball->hasComponent<kyra::TransformComponent2D>()) {
			auto ballPosition = ball->getComponent<kyra::TransformComponent2D>()->getPosition();
			auto padPosition = getNode()->getComponent<kyra::TransformComponent2D>()->getPosition();
			if ( (ballPosition.getX()-5) > padPosition.getX()) {
				padPosition = kyra::Vector2<float>(padPosition.getX() + (500 * deltaTime), padPosition.getY());
				getNode()->getComponent<kyra::TransformComponent2D>()->setPosition(padPosition);
				getNode()->getComponent<kyra::TransformComponent2D>()->markWorldDirty();
			}
			else if ( (ballPosition.getX()+5) < padPosition.getX()) {
				padPosition = kyra::Vector2<float>(padPosition.getX() - (500 * deltaTime), padPosition.getY());
				getNode()->getComponent<kyra::TransformComponent2D>()->setPosition(padPosition);
				getNode()->getComponent<kyra::TransformComponent2D>()->markWorldDirty();
			}
		}
	}
	virtual std::size_t getHash() const {
		return typeid(AIPadScriptComponent).hash_code();
	}

};

class BallScriptComponent : public kyra::ScriptComponent {

	bool m_Started = false;
	std::string m_LastCollision = "";

	bool onCollision(PhysicsComponent2D* component, PhysicsComponent2D* target) {
		if (m_LastCollision == target->getNode()->getName()) {
			return true;
		}
		m_LastCollision = target->getNode()->getName();
		kyra::Vector2<float> velocity = component->getVelocity();
		if (target->getNode()->getName() == "Pad1Node" || target->getNode()->getName() == "Pad2Node") {
			auto target_pos = target->getNode()->getComponent<kyra::TransformComponent2D>()->getPosition();
			auto pos = component->getNode()->getComponent<kyra::TransformComponent2D>()->getPosition();
			velocity = kyra::Vector2<float>(target_pos.getX() - pos.getX() + (float)(rand() % 200) - (float(rand() % 200)), -velocity.getY());
			component->addForce(velocity);
		}
		else if (target->getNode()->getName() == "TopWall" || target->getNode()->getName() == "BottomWall") {
			velocity = kyra::Vector2<float>(velocity.getX(), -velocity.getY());
			component->addForce(velocity);
		}
		else if (target->getNode()->getName() == "LeftWall" || target->getNode()->getName() == "RightWall") {
			velocity = kyra::Vector2<float>(-velocity.getX(), velocity.getY());
			component->addForce(velocity);
		}
	
		return true;
	}

public:

	void update(float deltaTime) final {
		kyra::Node* node = getNode();
		if (node->hasComponent<PhysicsComponent2D>()) {
			PhysicsComponent2D* physicsComponent = node->getComponent<PhysicsComponent2D>();
			if (!m_Started) {
				physicsComponent->addForce({ 250.f - (float)((rand() % 500)), -350.0f});
				physicsComponent->onCollision.connect(this, std::bind(&BallScriptComponent::onCollision, this, std::placeholders::_1, std::placeholders::_2));
				m_Started = true;
			}
		}
	}

	virtual std::size_t getHash() const {
		return typeid(BallScriptComponent).hash_code();
	}

};


class Pong : public kyra::Application {
	
public:

	bool onSetup() final {
		
		// Initialise window subsysten	

		kyra::WindowDescriptor windowDescriptor;
		windowDescriptor.title = "Pong";
		windowDescriptor.width = 1280;
		windowDescriptor.height = 720;
		windowDescriptor.fullscreen = false;

		kyra::Window* window = registerSystem<kyra::Window>();
		if (!window->init(windowDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialise window");
			return false;
		}

		// Initialise input subsystem
		
		kyra::InputManagerDescriptor inputManagerDescriptor;
		inputManagerDescriptor.window = window;
		
		kyra::InputManager* inputManager = registerSystem<kyra::InputManager>();
		if (!inputManager->init(inputManagerDescriptor)) {
			return false;
		}

		kyra::WindowEvents::onKeyUp.connect(this, [&](kyra::Key key) {
			if (key == kyra::Key::Escape) {
				quit();
				return true;
			}
			return false;
		});

		kyra::WindowEvents::onClose.connect(this, [&]() {
			quit();
			return true;
		});

		// Initialise asset manager
		kyra::AssetManager* assetManager = registerSystem<kyra::AssetManager>();


		// Initialise render subsystem
		
		kyra::RendererDescriptor rendererDescriptor;
		rendererDescriptor.type = kyra::RenderDeviceType::OpenGL;
		rendererDescriptor.window = window;
		rendererDescriptor.assetManager = assetManager;

		kyra::Renderer* renderer = registerSystem<kyra::Renderer>();
		if (!renderer->init(rendererDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialize renderer");
			return false;
		}
		renderer->registerRenderPassType<kyra::RenderPassPresent>("RenderPassPresent");
		renderer->registerRenderPassProcessorType<kyra::SceneRenderPassProcessor2D>("SceneRenderPassProcessor2D");

	
		// Initialise render pipeline

		constexpr const char* KYRA_RENDERPASS_PRESENT = "RenderPassPresent";

		kyra::RenderPassEntry renderPassEntry;
		renderPassEntry.name = KYRA_RENDERPASS_PRESENT;
		renderPassEntry.processorName = "SceneRenderPassProcessor2D";

		kyra::RenderPipelineDescriptor renderPipelineDescriptor;
		renderPipelineDescriptor.systemManager = getSystemManager();
		renderPipelineDescriptor.renderer = renderer;
		renderPipelineDescriptor.m_RenderPasses.emplace_back(renderPassEntry);

		kyra::RenderPipeline* renderPipeline = renderer->createRenderPipeline("DefaultPipeline");
		if (!renderPipeline->init(renderPipelineDescriptor)) {
			return false;
		}

		/*kyra::BinaryReader reader;
		reader.open("PongRenderPipeline.bin");
		renderPipelineDescriptor.read(reader);
		reader.close();*/


		/*kyra::BinaryWriter writer;
		writer.open("PongRenderPipeline.bin");
		renderPipelineDescriptor.write(writer);
		writer.close();*/



		// Initialise sript subsystem

		kyra::ScriptSystem* scriptSystem = registerSystem<kyra::ScriptSystem>();
		scriptSystem->registerScriptComponentType<PlayerPadScriptComponent>();
		scriptSystem->registerScriptComponentType<AIPadScriptComponent>();
		scriptSystem->registerScriptComponentType<BallScriptComponent>();

		// Initialise SceneSystem2D		
		
		kyra::SceneSystem2D* sceneSystem = registerSystem<kyra::SceneSystem2D>();
		kyra::Scene* scene = sceneSystem->createScene("DefaultScene");
		scene->setRenderPipeline(renderPipeline);
		sceneSystem->setActiveScene(scene);

		// Initialise physics System

		PhysicsSystem2D* physicsSystem = registerSystem<PhysicsSystem2D>();
	
		// Initialise Image Manager
		
		auto imageSystem = registerSystem<kyra::ImageManager>();

		// Initialise Audio Manager

		auto audioController = registerSystem<kyra::AudioController>();
		if (!audioController->init()) {
			return false;
		}

		// Initialise Assets

		kyra::TextureAsset::Handle ballTextureAsset = assetManager->loadTexture("./Assets/Textures/Ball.bmp");
		if(ballTextureAsset.isValid() == false) {
			KYRA_LOG_ERROR("Failed to load texture Asset: ./Assets/Textures/Ball.bmp");
			return false;
		}

		kyra::TextureAsset::Handle padTextureAsset = assetManager->loadTexture("./Assets/Textures/Pad.bmp");
		if(padTextureAsset.isValid() == false) {
			KYRA_LOG_ERROR("Failed to load texture Asset: ./Assets/Textures/Pad.bmp");
			return false;
		}

		kyra::TextureAsset::Handle backgroundTextureAsset = assetManager->loadTexture("./Assets/Textures/Background.bmp");
		if(backgroundTextureAsset.isValid() == false) {
			KYRA_LOG_ERROR("Failed to load texture Asset: ./Assets/Textures/Background.bmp");
			return false;
		}

		kyra::Node* backgroundNode = scene->createNode("Background");
		backgroundNode->addComponent(sceneSystem->createTransformComponent());
		auto* transformComponent = backgroundNode->getComponent<kyra::TransformComponent2D>();
		transformComponent->setPosition({ 0,0 });
		transformComponent->setSize({ 1280,720 });
		backgroundNode->addComponent(sceneSystem->createSpriteComponent());
		backgroundNode->getComponent<kyra::SpriteComponent>()->setTexture(backgroundTextureAsset);

		kyra::Node* ballNode = scene->createNode("BallNode");
		ballNode->addComponent(sceneSystem->createTransformComponent());
		ballNode->getComponent<kyra::TransformComponent2D>()->setPosition({ 0,500 });
		ballNode->getComponent<kyra::TransformComponent2D>()->setSize({ 10,10 });
		ballNode->addComponent(scriptSystem->create<BallScriptComponent>());
		ballNode->addComponent(sceneSystem->createSpriteComponent());
		ballNode->getComponent<kyra::SpriteComponent>()->setTexture(ballTextureAsset);
		ballNode->addComponent(physicsSystem->create());

		kyra::Node* pad1Node = scene->createNode("Pad1Node");
		pad1Node->addComponent(sceneSystem->createTransformComponent());
		pad1Node->getComponent<kyra::TransformComponent2D>()->setPosition({ 150,0 });
		pad1Node->getComponent<kyra::TransformComponent2D>()->setSize({ 100,20 });
		pad1Node->addComponent(physicsSystem->create());
		pad1Node->addComponent(sceneSystem->createSpriteComponent());
		pad1Node->getComponent<kyra::SpriteComponent>()->setTexture(padTextureAsset);
		pad1Node->addComponent(audioController->createAudioComponent());
		pad1Node->getComponent<kyra::AudioComponent>()->setBuffer(audioController->getAudioBuffer("./Assets/Audio/Example.wav"));
		pad1Node->addComponent(scriptSystem->create<PlayerPadScriptComponent>());

		kyra::Node* pad2Node = scene->createNode("Pad2Node");
		pad2Node->addComponent(sceneSystem->createTransformComponent());
		pad2Node->getComponent<kyra::TransformComponent2D>()->setPosition({ 150,700 });
		pad2Node->getComponent<kyra::TransformComponent2D>()->setSize({ 100,20 });
		pad2Node->addComponent(sceneSystem->createSpriteComponent());
		pad2Node->getComponent<kyra::SpriteComponent>()->setTexture(padTextureAsset);
		pad2Node->addComponent(scriptSystem->create<AIPadScriptComponent>());
		pad2Node->addComponent(physicsSystem->create());

		kyra::Node* leftWall = scene->createNode("LeftWall");
		leftWall->addComponent(sceneSystem->createTransformComponent());
		leftWall->getComponent<kyra::TransformComponent2D>()->setPosition({ -10,0 });
		leftWall->getComponent<kyra::TransformComponent2D>()->setSize({ 10,720 });
		leftWall->addComponent(physicsSystem->create());
		kyra::Node* rightWall = scene->createNode("RightWall");
		rightWall->addComponent(sceneSystem->createTransformComponent());
		rightWall->getComponent<kyra::TransformComponent2D>()->setPosition({ 1280,0 });
		rightWall->getComponent<kyra::TransformComponent2D>()->setSize({ 10,720 });
		rightWall->addComponent(physicsSystem->create());
		kyra::Node* toptWall = scene->createNode("TopWall");
		toptWall->addComponent(sceneSystem->createTransformComponent());
		toptWall->getComponent<kyra::TransformComponent2D>()->setPosition({ 0,-10 });
		toptWall->getComponent<kyra::TransformComponent2D>()->setSize({ 1280,10 });
		toptWall->addComponent(physicsSystem->create());
		kyra::Node* bottomWall = scene->createNode("BottomWall");
		bottomWall->addComponent(sceneSystem->createTransformComponent());
		bottomWall->getComponent<kyra::TransformComponent2D>()->setPosition({ 0,720 });
		bottomWall->getComponent<kyra::TransformComponent2D>()->setSize({ 1280,10 });
		bottomWall->addComponent(physicsSystem->create());

		return true;
	}


	virtual void onStart() final {
	
	}
	
	virtual void onExit() final {

	}

};

KYRA_DEFINE_APPLICATION(Pong);
