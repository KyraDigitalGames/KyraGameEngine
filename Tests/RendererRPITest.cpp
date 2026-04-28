
#include <KyraGameEngine/Window/WindowEvent.hpp>
#include <KyraGameEngine/Window/Windows/WindowWindows.hpp>
#include <KyraGameEngine/Renderer/RHI/RHIDevice.hpp>

#include <string>
#include <unordered_map>
#include <typeindex>

namespace kyra {

	struct RPIResource {

		enum class Access {
			Read,
			Write
		};

		static constexpr const char* WINDOW_SURFACE = "KYRA_WINDOW_SURFACE";

		std::string name;
		RPIResource::Access access;
	};


	class RPIRenderDataBuffer {
	public:
		template<typename T>
		void add(const T& data) {
			getBuffer<T>().push_back(data);
		}

		template<typename T>
		std::vector<T>& getBuffer() {
			auto& base = buffers[typeid(T)];
			if (!base) {
				base = std::make_unique<Holder<T>>();
			}
			return static_cast<Holder<T>*>(base.get())->data;
		}

		void clearAll() {
			buffers.clear();
		}

	private:
		struct BaseHolder {
			virtual ~BaseHolder() = default;
		};

		template<typename T>
		struct Holder : BaseHolder {
			std::vector<T> data;
		};

		std::unordered_map<std::type_index, std::unique_ptr<BaseHolder>> buffers;
	};



	class RPIRenderGraph;
	class RPIRenderPass {

		std::vector<RPIResource> m_Inputs;
		std::vector<RPIResource> m_Outputs;

	protected:

		void registerInput(const RPIResource& resource) {
			m_Inputs.push_back(resource);
		}

		void registerOutput(const RPIResource& resource) {
			m_Outputs.push_back(resource);
		}
			 
	public:
		virtual ~RPIRenderPass() = default;

		using Ptr = std::unique_ptr<RPIRenderPass>;

		virtual bool init(kyra::RHIDevice::Ptr& device) = 0;
		virtual void execute(kyra::RHICommandBuffer::Ptr& commandBuffer, RPIRenderDataBuffer& buffer) = 0;

	};


	class RPIRenderGraph {

		std::vector<RPIRenderPass*> m_RenderPasses;

		static void cullPasses(std::vector<RPIRenderPass::Ptr>& input, std::vector<RPIRenderPass*>& output) {
			for (auto& renderPass : input) {
				output.push_back(renderPass.get());
			}
		}

		static void orderPasses(std::vector<RPIRenderPass::Ptr>& input, std::vector<RPIRenderPass*>& output) {

		}

	public:

		void compile(std::vector<RPIRenderPass::Ptr>& renderPasses) {
			if (renderPasses.empty()) {
				return;
			}
			cullPasses(renderPasses, m_RenderPasses);
			orderPasses(renderPasses, m_RenderPasses);
		}

		void execute(kyra::RHICommandBuffer::Ptr& commandBuffer, RPIRenderDataBuffer& renderData) {
			if (m_RenderPasses.empty()) {
				return;
			}
			for (auto& renderPass : m_RenderPasses) {
				renderPass->execute(commandBuffer, renderData);
			}
		}

		void reset() {
			m_RenderPasses.clear();
		}

	};

	class RPISceneView {

	public:
		virtual ~RPISceneView() = default;

	};

	class RPIFeatureProcessor {

	public:
		virtual ~RPIFeatureProcessor() = default;

		using Ptr = std::unique_ptr<RPIFeatureProcessor>;

		virtual bool init(kyra::RHIDevice::Ptr& device) = 0;
		virtual void gather(RPIRenderDataBuffer& buffer) = 0;
	};



	class RPIRenderPipeline {

		RHIDevice::Ptr* m_RenderDevice;
		RPIRenderGraph m_RenderGraph;
		std::vector<RPIFeatureProcessor*> m_FeatureProcessors;
		std::vector<RPIRenderPass::Ptr> m_RenderPasses;
	public:

		struct Descriptor {
			Window::Ptr* window = nullptr;
			RHIDevice::Ptr* renderDevice = nullptr;
		};

		bool init(RPIRenderPipeline::Descriptor& descriptor) {
			m_RenderDevice = descriptor.renderDevice;
			return true;
		}
		
		void registerRenderPass(RPIRenderPass::Ptr renderPass) {
			m_RenderPasses.push_back(std::move(renderPass));
		}

		void registerFeatureProcessor(RPIFeatureProcessor* processor) {
			m_FeatureProcessors.push_back(processor);
			m_FeatureProcessors.back()->init(*m_RenderDevice);
		}
			
		void renderFrame(RHICommandBuffer::Ptr& commandBuffer) {
			kyra::RPIRenderDataBuffer buffer;
			for (auto& processor : m_FeatureProcessors) {
				processor->gather(buffer);
			}
			m_RenderGraph.compile(m_RenderPasses);
			m_RenderGraph.execute(commandBuffer,buffer);
		}

	};


}

struct Vertex {
	float position[3];
	float color[3];
};

struct TriangleRenderData {
	int temporaryValue = 0;
};

class TriangleView : public kyra::RPISceneView {

public:

};

class TriangleFeature : public kyra::RPIFeatureProcessor {

public:

	bool init(kyra::RHIDevice::Ptr& device) {
		return true;
	}

	virtual void gather(kyra::RPIRenderDataBuffer& buffer) {
		TriangleRenderData renderData;
		buffer.add(renderData);
	}

};

class TriangleRenderPass : public kyra::RPIRenderPass {

	kyra::RHIPipelineState::Ptr m_PipelineState;
	kyra::RHIBuffer::Ptr m_VertexBuffer;
	kyra::RHIRenderPass::Descriptor renderPassDescriptor;
	kyra::RHIRenderPass::Ptr m_RenderPass;

public:

	bool init(kyra::RHIDevice::Ptr& device) final {
		
		registerInput({
			"TEST_IMAGE",
			kyra::RPIResource::Access::Read 
		});

		registerOutput({
			kyra::RPIResource::WINDOW_SURFACE,
			kyra::RPIResource::Access::Write }
		);

		kyra::RHIShader::Descriptor vertexShaderDescriptor;
		vertexShaderDescriptor.type = kyra::RHIShader::Type::Vertex;
		vertexShaderDescriptor.data = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"out vec3 oColor;\n"
			"void main() {\n"
			"    gl_Position = vec4(aPos, 1.0);\n"
			"    oColor = aColor;\n"
			"}\0";
		vertexShaderDescriptor.size = 0;

		kyra::RHIShader::Ptr vertexShader = device->createShader(vertexShaderDescriptor);
		if (!vertexShader) {
			return false;
		}

		kyra::RHIShader::Descriptor fragmentShaderDescriptor;
		fragmentShaderDescriptor.type = kyra::RHIShader::Type::Fragment;
		fragmentShaderDescriptor.data = "#version 330 core\n"
			"in vec3 oColor;\n"
			"out vec4 vertexColor;\n"
			"void main() {\n"
			"vertexColor = vec4(oColor.r, oColor.g, oColor.b, 1.0);\n"
			"}\0";
		fragmentShaderDescriptor.size = 0;

		kyra::RHIShader::Ptr fragmentShader = device->createShader(fragmentShaderDescriptor);
		if (!fragmentShader) {
			return false;
		}

		kyra::RHIPipelineLayout::Descriptor pipelineLayoutDescriptor;
		kyra::RHIPipelineLayout::Ptr pipelineLayout = device->createPipelineLayout(pipelineLayoutDescriptor);
		if (!pipelineLayout) {
			return false;
		}

		kyra::RHIPipelineState::Descriptor pipelineStateDescriptor;
		pipelineStateDescriptor.fragmentShader = &fragmentShader;
		pipelineStateDescriptor.vertexShader = &vertexShader;
		pipelineStateDescriptor.pipelineLayout = &pipelineLayout;
		pipelineStateDescriptor.bufferLayout.stride = sizeof(Vertex);
		pipelineStateDescriptor.bufferLayout.attributes = {
			{0, kyra::RHIPipelineState::BufferLayoutAttribute::Format::Float, 3, 0},
			{1, kyra::RHIPipelineState::BufferLayoutAttribute::Format::Float, 3, 3 * sizeof(float)}
		};
		m_PipelineState = device->createPipelineState(pipelineStateDescriptor);
	
		Vertex vertices[] = {
			{{0,0.5,0}, {1,0,0}},
			{{-0.5,-0.5,0}, {0,1,0}},
			{{0.5,-0.5,0}, {0,0,1}}
		};

		kyra::RHIBuffer::Descriptor vertexBufferDescriptor;
		vertexBufferDescriptor.size = sizeof(vertices);
		vertexBufferDescriptor.usage = kyra::RHIBuffer::Type::Vertex;
		m_VertexBuffer = device->createBuffer(vertexBufferDescriptor);
		if (!m_VertexBuffer) {
			return false;
		}
		m_VertexBuffer->upload(vertices, sizeof(vertices));

		kyra::RHIRenderPass::Descriptor renderPassDescriptor;
		m_RenderPass = device->createRenderPass(renderPassDescriptor);


		return true;
	}

	void execute(kyra::RHICommandBuffer::Ptr& commandBuffer, kyra::RPIRenderDataBuffer& buffer) {
		std::vector<TriangleRenderData>& data = buffer.getBuffer<TriangleRenderData>();
		commandBuffer->beginRenderPass(m_RenderPass, nullptr);
		for (auto& renderData : data) {
			commandBuffer->bindPipeline(m_PipelineState);
			commandBuffer->bindVertexBuffer(0, m_VertexBuffer);
			commandBuffer->draw(0, 3);
		}
		commandBuffer->endRenderPass();
	}

};


class TestApplication {


	class EventHandler : public kyra::WindowEvent::Handler {

		bool m_IsQuitRequested = false;

	public:

		bool onClose() final {
			m_IsQuitRequested = true;
			return false;
		}

		bool isQuitRequested() const {
			return m_IsQuitRequested;
		}

	};
	EventHandler m_EventHandler;

public:

	int run(int argc, char** argv) {

		kyra::Window::Descriptor windowDescriptor;
		windowDescriptor.x = kyra::Window::WINDOW_POS_DEFAULT;
		windowDescriptor.y = kyra::Window::WINDOW_POS_DEFAULT;

		kyra::Window::Ptr window = kyra::Window::create();
		if (!window->init(windowDescriptor)) {
			return -1;
		}


		kyra::RHIDevice::Descriptor renderDeviceDescriptor;
		renderDeviceDescriptor.window = &window;
		kyra::RHIDevice::Ptr renderDevice = kyra::RHIDevice::create();
		if (!renderDevice->init(renderDeviceDescriptor)) {
			return -2;
		}

		kyra::RHISwapChain::Descriptor swapChainDescriptor;
		swapChainDescriptor.width = 1280;
		swapChainDescriptor.height = 720;
		kyra::RHISwapChain::Ptr m_SwapChain = renderDevice->createSwapChain(swapChainDescriptor);
		if (!m_SwapChain) {
			return -3;
		}

		kyra::RHIPipelineState::Ptr m_PipelineState;


		kyra::RPIRenderPipeline::Descriptor renderPipelineDescriptor;
		renderPipelineDescriptor.renderDevice = &renderDevice;
		kyra::RPIRenderPipeline renderPipeline;
		if (!renderPipeline.init(renderPipelineDescriptor)) {
			return -4;
		}

		kyra::RPIFeatureProcessor::Ptr triangleFeatureProcessor = std::make_unique<TriangleFeature>();
		renderPipeline.registerFeatureProcessor(triangleFeatureProcessor.get());

		kyra::RPIRenderPass::Ptr triangleRenderPass = std::make_unique<TriangleRenderPass>();
		if (!triangleRenderPass->init(renderDevice)) {
			return -5;
		}
		renderPipeline.registerRenderPass(std::move(triangleRenderPass));


		while (!m_EventHandler.isQuitRequested()) {
			window->processEvents();
			kyra::RHICommandQueue::Ptr commandQueue = renderDevice->createCommandQueue();
			kyra::RHICommandBuffer::Ptr commandBuffer = renderDevice->createCommandBuffer();
			uint32_t imageIndex = m_SwapChain->acquireNextImage();
			kyra::RHIFrameBuffer* framebuffer = m_SwapChain->getFrameBuffer(imageIndex);
			commandBuffer->begin();
			renderPipeline.renderFrame(commandBuffer);
			commandBuffer->end();
			commandQueue->submit(commandBuffer);
			m_SwapChain->present(imageIndex);
		}

		return 0;
	}

};

int main(int argc, char** argv) {
	return TestApplication().run(argc, argv);
}