
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

class Node;
class Component {

	Node* m_Node = nullptr;

public:
	virtual ~Component() = default;

	void setParent(Node* node) {
		m_Node = node;
	}

	Node* getNode() {
		return m_Node;
	}

	const Node* getNode() const {
		return m_Node;
	}

	virtual std::size_t getHash() const = 0;

};


class Node {

	std::map<std::size_t, Component*> m_Components;

	Node* m_Parent = nullptr;
	std::vector<Node*> m_Children;

public:

	std::vector<Node*>& getChildren() {
		return m_Children;
	}

	const std::vector<Node*>& getChildren() const {
		return m_Children;
	}

	void addComponent(Component* component) {
		auto id = component->getHash();
		component->setParent(this);
		m_Components.emplace(id, component);
	}

	template<class ComponentType>
	bool hasComponent() const {
		auto id = typeid(ComponentType).hash_code();
		auto it = m_Components.find(id);
		return it != m_Components.end();
	}

	template<class ComponentType>
	ComponentType* getComponent() {
		auto id = typeid(ComponentType).hash_code();
		auto it = m_Components.find(id);
		if(it != m_Components.end()) {
			return static_cast<ComponentType*>(it->second);
		}
		return nullptr;
	}

	template<class ComponentType>
	const ComponentType* getComponent() const {
		auto id = typeid(ComponentType).hash_code();
		auto it = m_Components.find(id);
		if (it != m_Components.end()) {
			return static_cast<ComponentType*>(it->second);
		}
		return nullptr;
	}

	void setParent(Node* node) {
		m_Parent = node;
	}

	Node* getParent() noexcept {
		return m_Parent;
	}

	const Node* getParent() const noexcept {
		return m_Parent;
	}

};

class TransformComponent : public Component {

	kyra::Vector3<float> m_Position;
	kyra::Vector3<float> m_Size;

	mutable kyra::Matrix4 m_LocalTransform;
	mutable bool m_IsLocalTransformDirty = true;

	mutable kyra::Matrix4 m_WorldTransform;
	mutable bool m_IsWorldTransformDirty = true;


	public:

	void markWorldDirty() {
		m_IsWorldTransformDirty = true;
		for (auto* c : getNode()->getChildren()) {
			if (c->hasComponent<TransformComponent>()) {
				c->getComponent<TransformComponent>()->markWorldDirty();
			}
		}
	}

	void setPosition(const kyra::Vector3<float>& position) {
		m_Position = position;
		m_IsLocalTransformDirty = true;
	}

	const kyra::Vector3<float>& getPosition() const {
		return m_Position;
	}

	void setSize(const kyra::Vector3<float>& size) {
		m_Size = size;
		m_IsLocalTransformDirty = true;
	}

	const kyra::Vector3<float>& getSize() const {
		return m_Size;
	}

	const kyra::Matrix4& getTransform() const {
		if (m_IsLocalTransformDirty) {
			m_LocalTransform = kyra::Matrix4()
				.scale(m_Size)
				.translate(m_Position);
			m_IsLocalTransformDirty = false;
			m_IsWorldTransformDirty = true;
		}
		if (m_IsWorldTransformDirty) {
			const Node* parentNode = getNode()->getParent();
			if (parentNode) {
				if (parentNode->hasComponent<TransformComponent>()) {
					const TransformComponent* parentTransform = parentNode->getComponent<TransformComponent>();
					m_WorldTransform = parentTransform->getTransform() * m_LocalTransform;
				}
				else {
					m_WorldTransform = m_LocalTransform;
				}
			}
			else {
				m_WorldTransform = m_LocalTransform;
			}
			m_IsWorldTransformDirty = false;
		}
		return m_WorldTransform;
	}

	virtual std::size_t getHash() const {
		return typeid(TransformComponent).hash_code();
	}

};

class ScriptComponentInterface : public Component {

public:
	virtual ~ScriptComponentInterface() = default;

	virtual void update(float deltaTime) = 0;
};

class ScriptComponentFactoryInterface {

public:
	virtual ~ScriptComponentFactoryInterface() = default;

	virtual std::unique_ptr<ScriptComponentInterface> create() = 0;

};

template<class ScriptComponentType>
class ScriptComponentFactory : public ScriptComponentFactoryInterface {

public:

	std::unique_ptr<ScriptComponentInterface> create() final {
		return std::make_unique<ScriptComponentType>();
	}
};

class ScriptSystem : public kyra::System {

	std::map<std::size_t, std::unique_ptr<ScriptComponentFactoryInterface>> m_Factories;
	std::vector<std::unique_ptr<ScriptComponentInterface>> m_Components;

public:

	template<class ScriptComponentType>
	void registerScriptComponentType() {
		auto id = typeid(ScriptComponentType).hash_code();
		m_Factories.emplace(id, std::make_unique<ScriptComponentFactory<ScriptComponentType>>());
	}

	template<class ScriptComponentType> 
	ScriptComponentType* create() {
		m_Components.emplace_back(m_Factories[typeid(ScriptComponentType).hash_code()]->create());
		return static_cast<ScriptComponentType*>(m_Components.back().get());
	}

	void update(float deltaTime) {
		for (auto& component : m_Components) {
			component->update(deltaTime);
		}
	}

};

class ScriptComponent : public ScriptComponentInterface {

public:

};


class Scene : public kyra::System {

	std::map<std::string, std::unique_ptr<Node>> m_Nodes;
	kyra::RenderPipeline m_RenderPipeline;

public:

	Node* createNode(const std::string& id) {
		auto it = m_Nodes.emplace(id, std::make_unique<Node>());
		return (it.second) ? it.first->second.get() : nullptr;
	}

	Node* getNode(const std::string& id) {
		auto it = m_Nodes.find(id);
		if (it == m_Nodes.end()) {
			return nullptr;
		}
		return it->second.get();
	}

	void setRenderPipeline(kyra::RenderPipeline renderPipeline) {
		m_RenderPipeline = renderPipeline;
	}

	void update(float deltaTime) {
		m_RenderPipeline.renderFrame();
	}

};

class SimpleMeshComponent : public Component {

public:

	const kyra::Matrix4& getTransform() const {
		return getNode()->getComponent<TransformComponent>()->getTransform();
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

	std::vector<std::unique_ptr<TransformComponent>> m_Components;

public:

	TransformComponent* create() {
		m_Components.emplace_back(std::make_unique<TransformComponent>());
		return m_Components.back().get();
	}

	void update(float deltaTime) final {

	}

};

class PhysicsComponent : public Component {
	
	public:
	
	virtual std::size_t getHash() const {
		return typeid(PhysicsComponent).hash_code();
	}

};

class PhysicsSystem : public kyra::System {

	public:
	void update(float deltaTime) final {

	}

};





class PlayerPadScriptComponent : public ScriptComponent {

public:

	void update(float deltaTime) final {
	Node* node = getNode();
		if(node->hasComponent<TransformComponent>()) {
			TransformComponent* transform = node->getComponent<TransformComponent>();
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

class AIPadScriptComponent : public ScriptComponent {
	
	public:
	
	void update(float deltaTime) final {
		// AI logic here
	}
	virtual std::size_t getHash() const {
		return typeid(AIPadScriptComponent).hash_code();
	}

};

class BallScriptComponent : public ScriptComponent {

public:

	void update(float deltaTime) final {
	
	}

	virtual std::size_t getHash() const {
		return typeid(BallScriptComponent).hash_code();
	}

};

	
class Pong : public kyra::Application {

	kyra::Window* m_Window;
	kyra::Renderer* m_Renderer;
	kyra::InputManager* m_InputManager;
	ScriptSystem* m_ScriptSystem;

	Scene* m_Scene;
	TransformSystem* m_TransformSystem;
	SimpleMeshSystem* m_SimpleMeshSystem;

	std::shared_ptr<SimpleRenderPassProcessor> m_SimpleRenderPassProcessor;

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

		m_ScriptSystem = registerSystem<ScriptSystem>();
		m_ScriptSystem->registerScriptComponentType<PlayerPadScriptComponent>();
		m_ScriptSystem->registerScriptComponentType<AIPadScriptComponent>();

		m_TransformSystem = registerSystem<TransformSystem>();

		m_Scene = registerSystem<Scene>();
		
		m_Renderer = registerSystem<kyra::Renderer>();
		kyra::RendererDescriptor rendererDescriptor;
		rendererDescriptor.type = kyra::RenderDeviceType::OpenGL;
		rendererDescriptor.window = m_Window;
		if (!m_Renderer->init(rendererDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialise renderer");
			return false;
		}

		kyra::RenderPipelineDescriptor renderPipelineDescriptor;
		renderPipelineDescriptor.commandBuffer = m_Renderer->acquireCommandBuffer();
		kyra::RenderPipeline renderPipeline;
		if (!renderPipeline.init(renderPipelineDescriptor)) {
			return false;
		}

		m_SimpleMeshSystem = registerSystem<SimpleMeshSystem>();

		m_SimpleRenderPassProcessor = std::make_shared<SimpleRenderPassProcessor>();

		kyra::RenderPassPresentDescriptor renderPassPresentDescriptor;
		renderPassPresentDescriptor.swapchain = m_Renderer->acquireSwapchain();
		renderPassPresentDescriptor.processor = m_SimpleRenderPassProcessor;
		if (!renderPipeline.registerPass<kyra::RenderPassPresent>(renderPassPresentDescriptor)) {
			return false;
		}

		SimpleRenderPassProcessor* processor = static_cast<SimpleRenderPassProcessor*>(renderPassPresentDescriptor.processor.get());
		processor->setSystemManager(getSystemManager());
		if(!processor->init(*m_Renderer)) {
			return false;
		};

	
		Node* ballNode = m_Scene->createNode("BallNode");
		ballNode->addComponent(m_TransformSystem->create());
		ballNode->getComponent<TransformComponent>()->setPosition({ 0,0,0 });
		ballNode->getComponent<TransformComponent>()->setSize({ 100,100,0 });
		ballNode->addComponent(m_SimpleMeshSystem->create());

		Node* pad1Node = m_Scene->createNode("Pad1Node");
		pad1Node->addComponent(m_TransformSystem->create());
		pad1Node->getComponent<TransformComponent>()->setPosition({ 150,150,0 });
		pad1Node->getComponent<TransformComponent>()->setSize({ 100,100,0 });
		pad1Node->addComponent(m_SimpleMeshSystem->create());
		pad1Node->addComponent(m_ScriptSystem->create<PlayerPadScriptComponent>());

		Node* pad2Node = m_Scene->createNode("Pad2Node");
		pad2Node->addComponent(m_TransformSystem->create());
		pad2Node->getComponent<TransformComponent>()->setPosition({ 300,300,0 });
		pad2Node->getComponent<TransformComponent>()->setSize({ 100,100,0 });
		pad2Node->addComponent(m_SimpleMeshSystem->create());
		pad2Node->addComponent(m_ScriptSystem->create<AIPadScriptComponent>());

		m_Scene->setRenderPipeline(renderPipeline);

		return true;
	}


	virtual void onStart() final {
	
	}
	
	virtual void onExit() final {

	}

};

KYRA_DEFINE_APPLICATION(Pong);
