
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
#include <KyraGameEngine/Scene/TransformComponent.hpp>
#include <KyraGameEngine/Scripting/ScriptSystem.hpp>
#include <KyraGameEngine/Scripting/ScriptComponent.hpp>
#include <KyraGameEngine/Scene/Scene.hpp>
#include <KyraGameEngine/GameModule/GameModule.hpp>


class SimpleMeshComponent : public kyra::Component {

public:

	const kyra::Matrix4& getTransform() const {
		return getNode()->getComponent<kyra::TransformComponent>()->getTransform();
	}

	virtual std::size_t getHash() const {
		return typeid(SimpleMeshComponent).hash_code();
	}


};


class SimpleMeshSystem : public kyra::System {

	std::vector<std::unique_ptr<SimpleMeshComponent>> m_Components;

public:

	SimpleMeshComponent* create() {
		m_Components.emplace_back(std::make_unique<SimpleMeshComponent>());
		return m_Components.back().get();
	}

	std::vector<std::unique_ptr<SimpleMeshComponent>>& getComponents() {
		return m_Components;
	}

	void update(float deltaTime) {

	}

};

class SimpleRenderPassProcessor : public kyra::RenderPassProcessor {

	std::shared_ptr<kyra::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<kyra::RenderPipelineState> m_RenderPipelineState;
	kyra::Matrix4 m_Projection;

public:

	bool init(kyra::Renderer& renderer) final {
	
		m_Projection = kyra::Matrix4::ortho(0, 1280, 720, 0, -1, 1);

		float vertices[] = {
			0,0,0,
			1,0,0,
			1,1,0,
			0,0,0,
			0,1,0,
			1,1,0
		};


		kyra::VertexBufferDescriptor vertexBufferDescriptor;
		vertexBufferDescriptor.size = 18*sizeof(float);
		vertexBufferDescriptor.data = vertices;
		m_VertexBuffer = renderer.createVertexBuffer();
		if (!m_VertexBuffer->init(vertexBufferDescriptor)) {
			return false;
		}

		kyra::ShaderDescriptor vertexShader;
		vertexShader.type = kyra::ShaderType::Vertex;
		vertexShader.language = kyra::ShaderLanguage::GLSL;
		vertexShader.data = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"uniform mat4 m_Projection;\n"
			"uniform mat4 m_Model;\n"
			"void main() {\n"
			"gl_Position = m_Projection * m_Model * vec4(aPos, 1.0);\n"
			"}\0";

		kyra::ShaderDescriptor fragmentShader;
		fragmentShader.type = kyra::ShaderType::Fragment;
		fragmentShader.language = kyra::ShaderLanguage::GLSL;
		fragmentShader.data = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main() {\n"
			"FragColor = vec4(1.0, 0.0,0.0, 1.0);\n"
			"}\0";;

		kyra::RenderPipelineStateDescriptor renderPipelineStateDescriptor;
		renderPipelineStateDescriptor.shaders.emplace_back(vertexShader);
		renderPipelineStateDescriptor.shaders.emplace_back(fragmentShader);
		m_RenderPipelineState = renderer.createRenderPipelineState();
		if (!m_RenderPipelineState->init(renderPipelineStateDescriptor)) {
			return false;
		}

		return true;
	}

	void update(kyra::CommandBuffer* commandBuffer) final {
		commandBuffer->bindVertexBuffer(m_VertexBuffer);
		commandBuffer->bindRenderPipelineState(m_RenderPipelineState);
		auto simpleMeshSystem = getSystem<SimpleMeshSystem>();
		for (auto& component : simpleMeshSystem->getComponents()) {
			commandBuffer->setUniformMat4(m_RenderPipelineState, "m_Projection", m_Projection);
			commandBuffer->setUniformMat4(m_RenderPipelineState, "m_Model", component->getTransform());
			commandBuffer->draw(0, 6);
		}
	}

};

class TransformSystem : public kyra::System {

	std::vector<std::unique_ptr<kyra::TransformComponent>> m_Components;

public:

	kyra::TransformComponent* create() {
		m_Components.emplace_back(std::make_unique<kyra::TransformComponent>());
		return m_Components.back().get();
	}

	void update(float deltaTime) final {

	}

};

class PhysicsComponent : public kyra::Component {
	
	kyra::Vector3<float> m_Velocity;

	public:
	
	void addForce(const kyra::Vector3<float>& vec) {
		m_Velocity = vec;
	}

	const kyra::Vector3<float>& getVelocity() const {
		return m_Velocity;
	}

	virtual std::size_t getHash() const {
		return typeid(PhysicsComponent).hash_code();
	}

	kyra::Signal<PhysicsComponent*> onCollision;

};

class PhysicsSystem : public kyra::System {

	std::vector<std::unique_ptr<PhysicsComponent>> m_Components;



	bool checkAABBOverlap(const kyra::Vector3<float>& posA, const kyra::Vector3<float>& sizeA,
		const kyra::Vector3<float>& posB, const kyra::Vector3<float>& sizeB) {
		return (posA.getX() < posB.getX() + sizeB.getX() &&
			posA.getX() + sizeA.getX() > posB.getX() &&
			posA.getY() < posB.getY() + sizeB.getY() &&
			posA.getY() + sizeA.getY() > posB.getY());
	}


public:
	void update(float deltaTime) final {
		for (auto& component : m_Components) {
			kyra::TransformComponent* transform = component->getNode()->getComponent<kyra::TransformComponent>();
			kyra::Vector3<float> position = transform->getPosition();
			auto velocity = component->getVelocity();
			position += kyra::Vector3<float>(velocity.getX() * deltaTime, velocity.getY() * deltaTime, 0);
			transform->setPosition(position);
			transform->markWorldDirty();
		}
		for (auto& component : m_Components) {
			kyra::TransformComponent* transformA = component->getNode()->getComponent<kyra::TransformComponent>();
			kyra::Vector3<float> positionA = transformA->getPosition();
			kyra::Vector3<float> sizeA = transformA->getSize();
			for (auto& otherComponent : m_Components) {
				if (component.get() == otherComponent.get()) {
					continue;
				}
				kyra::TransformComponent* transformB = otherComponent->getNode()->getComponent<kyra::TransformComponent>();
				kyra::Vector3<float> positionB = transformB->getPosition();
				kyra::Vector3<float> sizeB = transformB->getSize();
				if (checkAABBOverlap(positionA, sizeA, positionB, sizeB)) {
					component->onCollision.dispatch(component.get());
				}
			}
		}
	}

	PhysicsComponent* create() {
		m_Components.emplace_back(std::make_unique<PhysicsComponent>());
		return m_Components.back().get();
	}

};


class PlayerPadScriptComponent : public kyra::ScriptComponent {

public:

	void update(float deltaTime) final {
	kyra::Node* node = getNode();
		if(node->hasComponent<kyra::TransformComponent>()) {
			kyra::TransformComponent* transform = node->getComponent<kyra::TransformComponent>();
			kyra::Vector3<float> position = transform->getPosition();
			if(kyra::Keyboard::isPressed(kyra::Key::Left)) {
				position = kyra::Vector3<float>(position.getX() - (500*deltaTime), 0, 0);
			}
			if(kyra::Keyboard::isPressed(kyra::Key::Right)) {
				position = kyra::Vector3<float>(position.getX() + (500*deltaTime), 0, 0);
			}
			transform->setPosition(position);
			transform->markWorldDirty();
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
	}
	virtual std::size_t getHash() const {
		return typeid(AIPadScriptComponent).hash_code();
	}

};

class BallScriptComponent : public kyra::ScriptComponent {

	bool m_Started = false;

	bool onCollision(PhysicsComponent* component) {
		kyra::Vector3<float> velocity = component->getVelocity();
		velocity = kyra::Vector3<float>(velocity.getX(), -velocity.getY(), 0);
		component->addForce(velocity);
		return true;
	}

public:

	void update(float deltaTime) final {
		kyra::Node* node = getNode();
		
		if (node->hasComponent<PhysicsComponent>()) {
			PhysicsComponent* physicsComponent = node->getComponent<PhysicsComponent>();
			if (!m_Started) {
				physicsComponent->addForce({ 0.0f, -150.0f, 0.0f });
				physicsComponent->onCollision.connect(this, std::bind(&BallScriptComponent::onCollision, this, std::placeholders::_1));
				m_Started = true;
			}
		}
	}

	virtual std::size_t getHash() const {
		return typeid(BallScriptComponent).hash_code();
	}

};


class Pong : public kyra::Application {

	kyra::Window* m_Window = nullptr;
	kyra::Renderer* m_Renderer = nullptr;
	kyra::InputManager* m_InputManager = nullptr;
	kyra::ScriptSystem* m_ScriptSystem = nullptr;

	kyra::Scene* m_Scene = nullptr;
	TransformSystem* m_TransformSystem = nullptr;
	SimpleMeshSystem* m_SimpleMeshSystem = nullptr;
	PhysicsSystem* m_PhysicsSystem = nullptr;

	std::shared_ptr<SimpleRenderPassProcessor> m_SimpleRenderPassProcessor;
	std::shared_ptr<kyra::RenderPass> m_RenderPassPresent;

	kyra::Registry<kyra::RenderPass> m_RenderPassRegistry;
	kyra::Registry<kyra::RenderPassProcessor> m_RenderPassProcessorRegistry;

public:

	bool onSetup() final {
		
	
		m_Window = registerSystem<kyra::Window>();
		kyra::WindowDescriptor windowDescriptor;
		windowDescriptor.title = "Pong";
		windowDescriptor.width = 1280;
		windowDescriptor.height = 720;
		if (!m_Window->init(windowDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialise window");
			return false;
		}

		m_InputManager = registerSystem<kyra::InputManager>();
		kyra::InputManagerDescriptor inputManagerDescriptor;
		inputManagerDescriptor.window = m_Window;
		if (!m_InputManager->init(inputManagerDescriptor)) {
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

		m_ScriptSystem = registerSystem<kyra::ScriptSystem>();
		m_ScriptSystem->registerScriptComponentType<PlayerPadScriptComponent>();
		m_ScriptSystem->registerScriptComponentType<AIPadScriptComponent>();
		m_ScriptSystem->registerScriptComponentType<BallScriptComponent>();

		m_TransformSystem = registerSystem<TransformSystem>();

		m_Scene = registerSystem<kyra::Scene>();
		
		m_Renderer = registerSystem<kyra::Renderer>();
		kyra::RendererDescriptor rendererDescriptor;
		rendererDescriptor.type = kyra::RenderDeviceType::OpenGL;
		rendererDescriptor.window = m_Window;
		if (!m_Renderer->init(rendererDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialize renderer");
			return false;
		}


		m_RenderPassRegistry.registerFactory<kyra::RenderPassPresent>("RenderPassPresent");
		m_RenderPassProcessorRegistry.registerFactory<SimpleRenderPassProcessor>("SimpleRenderPassProcessor");


	
		kyra::RenderPipelineDescriptor renderPipelineDescriptor;

		/*kyra::BinaryReader reader;
		reader.open("PongRenderPipeline.bin");
		renderPipelineDescriptor.read(reader);
		reader.close();*/

		constexpr const char* KYRA_RENDERPASS_PRESENT = "RenderPassPresent";

		kyra::RenderPassEntry renderPassEntry;
		renderPassEntry.name = KYRA_RENDERPASS_PRESENT;
		renderPassEntry.processorName = "SimpleRenderPassProcessor";

		renderPipelineDescriptor.renderPassRegistry = &m_RenderPassRegistry;
		renderPipelineDescriptor.renderPassProcessorRegistry = &m_RenderPassProcessorRegistry;
		renderPipelineDescriptor.systemManager = getSystemManager();
		renderPipelineDescriptor.renderer = m_Renderer;
		renderPipelineDescriptor.m_RenderPasses.emplace_back(renderPassEntry);

		kyra::RenderPipeline renderPipeline;
		if (!renderPipeline.init(renderPipelineDescriptor)) {
			return false;
		}

		/*kyra::BinaryWriter writer;
		writer.open("PongRenderPipeline.bin");
		renderPipelineDescriptor.write(writer);
		writer.close();*/


		m_SimpleMeshSystem = registerSystem<SimpleMeshSystem>();

		m_PhysicsSystem = registerSystem<PhysicsSystem>();
	
		kyra::Node* ballNode = m_Scene->createNode("BallNode");
		ballNode->addComponent(m_TransformSystem->create());
		ballNode->getComponent<kyra::TransformComponent>()->setPosition({ 0,500,0 });
		ballNode->getComponent<kyra::TransformComponent>()->setSize({ 100,100,0 });
		ballNode->addComponent(m_ScriptSystem->create<BallScriptComponent>());
		ballNode->addComponent(m_SimpleMeshSystem->create());
		ballNode->addComponent(m_PhysicsSystem->create());

		kyra::Node* pad1Node = m_Scene->createNode("Pad1Node");
		pad1Node->addComponent(m_TransformSystem->create());
		pad1Node->getComponent<kyra::TransformComponent>()->setPosition({ 150,150,0 });
		pad1Node->getComponent<kyra::TransformComponent>()->setSize({ 100,100,0 });
		pad1Node->addComponent(m_PhysicsSystem->create());
		pad1Node->addComponent(m_SimpleMeshSystem->create());
		pad1Node->addComponent(m_ScriptSystem->create<PlayerPadScriptComponent>());

		kyra::Node* pad2Node = m_Scene->createNode("Pad2Node");
		pad2Node->addComponent(m_TransformSystem->create());
		pad2Node->getComponent<kyra::TransformComponent>()->setPosition({ 300,300,0 });
		pad2Node->getComponent<kyra::TransformComponent>()->setSize({ 100,100,0 });
		pad2Node->addComponent(m_SimpleMeshSystem->create());
		pad2Node->addComponent(m_ScriptSystem->create<AIPadScriptComponent>());
		pad2Node->addComponent(m_PhysicsSystem->create());

		m_Scene->setRenderPipeline(std::move(renderPipeline));

		return true;
	}


	virtual void onStart() final {
	
	}
	
	virtual void onExit() final {

	}

};

KYRA_DEFINE_APPLICATION(Pong);
