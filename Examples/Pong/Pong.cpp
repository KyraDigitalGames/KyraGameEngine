
#include <KyraGameEngine/Application/Application.hpp>
#include <KyraGameEngine/Renderer/Renderer.hpp>
#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Renderer/RenderPipeline.hpp>
#include <KyraGameEngine/Renderer/RenderPassPresent.hpp>
#include <KyraGameEngine/Renderer/RenderPassProcessor.hpp>
#include <KyraGameEngine/Math/Matrix4.hpp>

#include <Windows.h>
#include <gl/GL.h>

#include <map>


class Node;
class Component {

	Node* m_Parent = nullptr;

public:
	virtual ~Component() = default;

	void setParent(Node* node) {
		m_Parent = node;
	}

	Node* getParent() {
		return m_Parent;
	}

};


class Node {

	std::vector<std::shared_ptr<Component>> m_Components;

public:

	void addComponent(std::shared_ptr<Component> component) {
		component->setParent(this);
		m_Components.emplace_back(component);
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

	std::shared_ptr<kyra::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<kyra::RenderPipelineState> m_RenderPipelineState;
	std::vector<SimpleMeshComponent*> m_Components;
	kyra::Matrix4 m_Projection;

public:

	void addComponent(SimpleMeshComponent* component) {
		m_Components.push_back(component);
	}

	bool init(kyra::Renderer& renderer) final {
	
		m_Projection = kyra::Matrix4::ortho(0, 1280, 0, 720, -1, 1);

		float vertices[] = {
			0,0,
			0,10,
			10,10,
			0,0,
			10,0,
			10,10
		};

		kyra::VertexBufferDescriptor vertexBufferDescriptor;
		vertexBufferDescriptor.size = sizeof(vertices);
		vertexBufferDescriptor.data = vertices;
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
		for (auto& component : m_Components) {
			commandBuffer->bindVertexBuffer(m_VertexBuffer);
			commandBuffer->bindRenderPipelineState(m_RenderPipelineState);
			commandBuffer->setUniformMat4(m_RenderPipelineState, "m_Projection", m_Projection);
			commandBuffer->draw(0, 6);
		}
	}

};

class SimpleSystem {

	SimpleRenderPassProcessor m_Processor;

public:

	bool init(kyra::Renderer& renderer) {
		return m_Processor.init(renderer);
	}

	kyra::RenderPassProcessor* getProcessor() {
		return &m_Processor;
	}

	std::shared_ptr<SimpleMeshComponent> createSimpleMeshComponent() {
		auto component = std::make_shared<SimpleMeshComponent>();
		m_Processor.addComponent(component.get());
		return std::move(component);
	}

};

class Pong : public kyra::Application {

	kyra::Window m_Window;
	kyra::Renderer m_Renderer;
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

		kyra::RendererDescriptor rendererDescriptor;
		rendererDescriptor.type = kyra::RenderDeviceType::OpenGL;
		rendererDescriptor.window = &m_Window;
		if (!m_Renderer.init(rendererDescriptor)) {
			KYRA_LOG_ERROR("Failed to initialise renderer");
			return false;
		}

		if (!m_System.init(m_Renderer)) {
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
		renderPassPresentDescriptor.processor = m_System.getProcessor();
		if (!renderPipeline.registerPass<kyra::RenderPassPresent>(renderPassPresentDescriptor)) {
			return false;
		}



		Node* ballNode = m_Scene.createNode("BallNode");
		auto simpleComponent = m_System.createSimpleMeshComponent();
		ballNode->addComponent(simpleComponent);

		Node* pad1Node = m_Scene.createNode("Pad1Node");
		simpleComponent = m_System.createSimpleMeshComponent();
		pad1Node->addComponent(simpleComponent);

		Node* pad2Node = m_Scene.createNode("Pad2Node");
		simpleComponent = m_System.createSimpleMeshComponent();
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
