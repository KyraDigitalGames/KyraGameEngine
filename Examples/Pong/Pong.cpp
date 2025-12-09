
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

class BaseNode {

public:
	virtual ~BaseNode() = default;

	virtual const kyra::Vector2<float>& getPosition() const = 0;
	virtual void setPosition(const kyra::Vector2<float>& position) = 0;
	virtual const kyra::Vector2<float>& getSize() const = 0;
	virtual void setSize(const kyra::Vector2<float>& size) = 0;


};

class Component {

	BaseNode* m_Parent = nullptr;

public:
	virtual ~Component() = default;

	void setParent(BaseNode* node) {
		m_Parent = node;
	}

	BaseNode* getParent() {
		return m_Parent;
	}

	void setPosition(const kyra::Vector2<float>& position) {
		m_Parent->setPosition(position);
	}

	void setSize(const kyra::Vector2<float>& size) {
		m_Parent->setSize(size);
	}

	const kyra::Vector2<float>& getPosition() const {
		return m_Parent->getPosition();
	}

	const kyra::Vector2<float>& getSize() const {
		return m_Parent->getSize();
	}

};


class Node : public BaseNode{

	kyra::Vector2<float> m_Position;
	kyra::Vector2<float> m_Size; 
	std::vector<std::shared_ptr<Component>> m_Components;

public:

	void addComponent(std::shared_ptr<Component> component) {
		component->setParent(this);
		m_Components.emplace_back(component);
	}

	void setPosition(const kyra::Vector2<float>& position) {
		m_Position = position;
	}

	const kyra::Vector2<float>& getPosition() const {
		return m_Position;
	}

	void setSize(const kyra::Vector2<float>& size) {
		m_Size = size;
	}

	const kyra::Vector2<float>& getSize() const {
		return m_Size;
	}

};

class Scene {

	std::map<std::string, Node> m_Nodes;
	kyra::RenderPipeline m_RenderPipeline;

public:

	Node* createNode(const std::string& id) {
		m_Nodes[id] = Node();
		return &m_Nodes[id];
	}

	Node* getNode(const std::string& id) {
		auto it = m_Nodes.find(id);
		if (it == m_Nodes.end()) {
			return nullptr;
		}
		return &(it->second);
	}

	void setRenderPipeline(kyra::RenderPipeline renderPipeline) {
		m_RenderPipeline = renderPipeline;
	}

	void update() {
		m_RenderPipeline.renderFrame();
	}

};

class SimpleMeshComponent : public Component {

public:

};


class SimpleRenderPassProcessor : public kyra::RenderPassProcessor {

	std::vector<kyra::Vector2<float>> m_VertexArray;
	std::shared_ptr<kyra::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<kyra::RenderPipelineState> m_RenderPipelineState;
	std::vector<SimpleMeshComponent*> m_Components;
	kyra::Matrix4 m_Projection;

public:

	void addComponent(SimpleMeshComponent* component) {
		m_Components.push_back(component);
	}

	bool init(kyra::Renderer& renderer) final {
	
		m_Projection = kyra::Matrix4::ortho(0, 1280, 720, 0, -1, 1);

		m_VertexArray.resize(18);

		kyra::VertexBufferDescriptor vertexBufferDescriptor;
		vertexBufferDescriptor.size = 36*sizeof(float);
		vertexBufferDescriptor.data = nullptr;
		m_VertexBuffer = renderer.createVertexBuffer();
		if (!m_VertexBuffer->init(vertexBufferDescriptor)) {
			return false;
		}

		kyra::ShaderDescriptor vertexShader;
		vertexShader.type = kyra::ShaderType::Vertex;
		vertexShader.language = kyra::ShaderLanguage::GLSL;
		vertexShader.data = "#version 330 core\n"
			"layout (location = 0) in vec2 aPos;\n"
			"uniform mat4 m_Projection;\n"
			"void main() {\n"
			"gl_Position = m_Projection * vec4(aPos,0.0, 1.0);\n"
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
		int i = 0;
		for (auto& component : m_Components) {
			const kyra::Vector2<float> position = component->getPosition();
			const kyra::Vector2<float> size = component->getSize();
			m_VertexArray[i] = position;
			m_VertexArray[i + 1] = { position.getX() + size.getX(), position.getY() };
			m_VertexArray[i+2] = { position.getX() + size.getX(), position.getY() + size.getY()  };
			m_VertexArray[i+3] = position;
			m_VertexArray[i+4] = { position.getX(), position.getY() + size.getY() };
			m_VertexArray[i+5] = { position.getX() + size.getX(), position.getY() + size.getY() };
			i += 6;
		}
		commandBuffer->bindVertexBuffer(m_VertexBuffer);
		kyra::VertexBufferDescriptor descriptor;
		descriptor.data = &m_VertexArray[0];
		descriptor.size = 36 * sizeof(float);
		commandBuffer->updateBuffer(m_VertexBuffer, descriptor);

		commandBuffer->bindRenderPipelineState(m_RenderPipelineState);
		commandBuffer->setUniformMat4(m_RenderPipelineState, "m_Projection", m_Projection);
		commandBuffer->draw(0, 18);
	}

};


class AbstractSystem {

public:
	virtual ~AbstractSystem() = default;

	virtual bool init(kyra::Renderer* renderer) = 0;

	virtual std::shared_ptr<Component> createComponentByString(const std::string& id) = 0;
	virtual std::shared_ptr<Component> createComponentByHash(std::size_t hash) = 0;
	virtual std::shared_ptr<kyra::RenderPassProcessor> createRenderPassProcessorByString(const std::string& id) = 0;
	virtual std::shared_ptr<kyra::RenderPassProcessor> createRenderPassProcessorByHash(std::size_t hash) = 0;
	
	virtual std::size_t getHash() const = 0;

};


class EngineContext {

	std::map<std::string, std::shared_ptr<Component>> m_ComponentMap;
	std::map<std::string, std::shared_ptr<AbstractSystem>> m_SystemMap;
	std::map<std::string, std::shared_ptr<kyra::RenderPassProcessor>> m_RenderPassProcessorMap;

public:


};

class Module {

public:
	virtual ~Module() = default;

	virtual bool init(EngineContext& context) = 0;

};

class ScriptingModule : public Module {

public:
	virtual ~ScriptingModule() = default;

	virtual bool init(EngineContext& context) = 0;

};


class SimpleSystem : public AbstractSystem {

	kyra::Renderer* m_Renderer = nullptr;

public:

	bool init(kyra::Renderer* renderer) {
		m_Renderer = renderer;
		return true;
	}

	virtual std::shared_ptr<Component> createComponentByString(const std::string& id) {
		if (id == "SimpleMeshComponent") {
			return std::make_shared<SimpleMeshComponent>();
		}
		return nullptr;
	}

	virtual std::shared_ptr<Component> createComponentByHash(std::size_t hash) {
		return nullptr;
	}

	virtual std::shared_ptr<kyra::RenderPassProcessor> createRenderPassProcessorByString(const std::string& id) {
		if (id == "SimpleRenderPassProcessor") {
			auto processor = std::make_shared<SimpleRenderPassProcessor>();
			if (!processor->init(*m_Renderer)) {
				return nullptr;
			}
			return processor;
		}
		return nullptr;
	}
	
	virtual std::shared_ptr<kyra::RenderPassProcessor> createRenderPassProcessorByHash(std::size_t hash) {
		return nullptr;
	}

	std::size_t getHash() const {
		return typeid(SimpleSystem).hash_code();
	}
};

class ScriptingSystem : public AbstractSystem {

public:

	virtual bool init(kyra::Renderer* renderer) {
		return true;
	}

	virtual std::shared_ptr<Component> createComponentByString(const std::string& id) {
		return nullptr;
	}

	virtual std::shared_ptr<Component> createComponentByHash(std::size_t hash) {
		return nullptr;
	}

	virtual std::shared_ptr<kyra::RenderPassProcessor> createRenderPassProcessorByString(const std::string& id) {
		return nullptr;
	}

	virtual std::shared_ptr<kyra::RenderPassProcessor> createRenderPassProcessorByHash(std::size_t hash) {
		return nullptr;
	}

	std::size_t getHash() const {
		return typeid(ScriptingSystem).hash_code();
	}

};


class PadPlayerActor : public kyra::Actor {

public:

	void update() {
		if (kyra::Keyboard::isPressed(kyra::Key::Left)) {

		}
		if (kyra::Keyboard::isPressed(kyra::Key::Right)) {

		}
	}

};

	
class Pong : public kyra::Application {

	kyra::Window m_Window;
	kyra::Renderer m_Renderer;
	kyra::InputManager m_InputManager;
	ScriptingSystem m_ScriptingSystem;
	Scene m_Scene;
	SimpleSystem m_System;

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

		kyra::InputManagerDescriptor inputManagerDescriptor;
		inputManagerDescriptor.window = &m_Window;
		if (!m_InputManager.init(inputManagerDescriptor)) {
			return false;
		}

		kyra::WindowEvents::onKeyUp.connect(this, [&](kyra::Key key) {
			if(key == kyra::Key::Escape)
			quit();
			return true;
		});

		kyra::RendererDescriptor rendererDescriptor;
		rendererDescriptor.type = kyra::RenderDeviceType::OpenGL;
		rendererDescriptor.window = &m_Window;
		if (!m_Renderer.init(rendererDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialise renderer");
			return false;
		}

		if (!m_System.init(&m_Renderer)) {
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
		renderPassPresentDescriptor.processor = m_System.createRenderPassProcessorByString("SimpleRenderPassProcessor");
		if (!renderPipeline.registerPass<kyra::RenderPassPresent>(renderPassPresentDescriptor)) {
			return false;
		}

		SimpleRenderPassProcessor* processor = static_cast<SimpleRenderPassProcessor*>(renderPassPresentDescriptor.processor.get());

		Node* ballNode = m_Scene.createNode("BallNode");
		ballNode->setPosition({ 0,0 });
		ballNode->setSize({ 100,100 });
		auto simpleComponent = m_System.createComponentByString("SimpleMeshComponent");
		processor->addComponent(static_cast<SimpleMeshComponent*>(simpleComponent.get()));
		ballNode->addComponent(simpleComponent);

		Node* pad1Node = m_Scene.createNode("Pad1Node");
		pad1Node->setPosition({ 150,150 });
		pad1Node->setSize({ 150,150 });
		simpleComponent = m_System.createComponentByString("SimpleMeshComponent");
		processor->addComponent(static_cast<SimpleMeshComponent*>(simpleComponent.get()));
		pad1Node->addComponent(simpleComponent);

		Node* pad2Node = m_Scene.createNode("Pad2Node");
		pad2Node->setPosition({ 400,400 });
		pad2Node->setSize({ 200,200 });
		simpleComponent = m_System.createComponentByString("SimpleMeshComponent");
		processor->addComponent(static_cast<SimpleMeshComponent*>(simpleComponent.get()));
		pad2Node->addComponent(simpleComponent);

		m_Scene.setRenderPipeline(renderPipeline);

		return true;
	}


	virtual void onStart() final {
	
	}
	
	virtual void onUpdate() final {
		if (!m_Window.isOpen()) {
			quit();
		}
		m_Window.processEvents();
		m_Scene.update();
	}
	
	virtual void onExit() final {

	}

};

KYRA_DEFINE_APPLICATION(Pong);
