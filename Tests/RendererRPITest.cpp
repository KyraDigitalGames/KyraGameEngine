
#include <KyraGameEngine/Window/WindowEvent.hpp>
#include <KyraGameEngine/Window/Windows/WindowWindows.hpp>
#include <KyraGameEngine/Renderer/RHI/RHIDevice.hpp>

#include <string>
#include <unordered_map>
#include <typeindex>

namespace kyra {

	struct RPIResource {
		std::string name;
	};

	struct RPIResourceUsage {

		enum class Access {
			Read,
			Write
		};

		RPIResource* resource;
		RPIResourceUsage::Access access;

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



	class RPIRenderPass {

		std::vector<RPIResourceUsage> m_Inputs;
		std::vector<RPIResourceUsage> m_Outputs;

	public:
		virtual ~RPIRenderPass() = default;

		using Ptr = std::unique_ptr<RPIRenderPass>;

		virtual bool init(kyra::RHIDevice::Ptr& device) = 0;
		virtual void execute(kyra::RHICommandBuffer::Ptr& commandBuffer, RPIRenderDataBuffer& buffer) = 0;

	};

	//class RPITransientResourceAllocator {

	//};

	class RPIRenderGraph {

		std::vector<RPIRenderPass*> m_RenderPassesPtr;

	public:

		bool init(RHIDevice::Ptr& renderDevice) {
			return true;
		}

		void compile(std::vector<RPIRenderPass*>& renderPasses) {
			m_RenderPassesPtr.clear();
			for (auto& renderPass : renderPasses) {
				m_RenderPassesPtr.push_back(renderPass);
			}
		}

		void execute(kyra::RHICommandBuffer::Ptr& commandBuffer, RPIRenderDataBuffer& buffer) {
			for (auto& renderPass : m_RenderPassesPtr) {
				renderPass->execute(commandBuffer, buffer);
			}
		}

	};

	class RPIFeatureProcessor {

	public:
		virtual ~RPIFeatureProcessor() = default;

		using Ptr = std::unique_ptr<RPIFeatureProcessor>;

		virtual bool init(kyra::RHIDevice::Ptr& device) = 0;
		virtual void gather(RPIRenderDataBuffer& buffer) = 0;
	};



	class RPIRenderPipeline {

		RPIRenderGraph renderGraph;
		std::vector<RPIRenderPass*> m_RenderPasses;
		
	public:

		bool init(RHIDevice::Ptr& renderDevice) {
			return renderGraph.init(renderDevice);;
		}
		
		void registerRenderPass(RPIRenderPass* renderPass) {
			m_RenderPasses.push_back(renderPass);
		}
			
		void renderFrame(RPIRenderDataBuffer& buffer, RHICommandBuffer::Ptr& commandBuffer) {
			renderGraph.compile(m_RenderPasses);
			renderGraph.execute(commandBuffer, buffer);
		}

	};


}

struct Vertex {
	float position[3];
	float color[3];
};

struct TriangleRenderData {
	kyra::RHIBuffer* vertexBuffer = nullptr;
};

class TriangleFeature : public kyra::RPIFeatureProcessor {

	kyra::RHIBuffer::Ptr m_VertexBuffer;

	//kyra::RHIBuffer::Ptr m_UniformBuffer;
	//kyra::RHITexture::Ptr m_Texture;
	//kyra::RHISampler::Ptr m_Sampler;

public:

	bool init(kyra::RHIDevice::Ptr& device) {
		// Create Vertex Buffer

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
		return true;
	}

	virtual void gather(kyra::RPIRenderDataBuffer& buffer) {
		TriangleRenderData renderData;
		renderData.vertexBuffer = m_VertexBuffer.get();
		buffer.add(renderData);
	}

};

class TriangleRenderPass : public kyra::RPIRenderPass {

	kyra::RHIPipelineState::Ptr m_PipelineState;
	kyra::RHIRenderPass::Ptr m_RenderPass;

public:

	bool init(kyra::RHIDevice::Ptr& device) {
		
		// Create Pipeline State

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

		kyra::RHIRenderPass::Descriptor renderPassDescriptor;
		m_RenderPass = device->createRenderPass(renderPassDescriptor);
		if (!m_RenderPass) {
			return false;
		}

		struct Vertex {
			float position[3];
			float color[3];
		};

		kyra::RHIPipelineState::Descriptor pipelineStateDescriptor;
		pipelineStateDescriptor.fragmentShader = &fragmentShader;
		pipelineStateDescriptor.vertexShader = &vertexShader;
		pipelineStateDescriptor.renderPass = &m_RenderPass;
		pipelineStateDescriptor.pipelineLayout = &pipelineLayout;
		pipelineStateDescriptor.bufferLayout.stride = sizeof(Vertex);
		pipelineStateDescriptor.bufferLayout.attributes = {
			{0, kyra::RHIPipelineState::BufferLayoutAttribute::Format::Float, 3, 0},
			{1, kyra::RHIPipelineState::BufferLayoutAttribute::Format::Float, 3, 3 * sizeof(float)}
		};

		m_PipelineState = device->createPipelineState(pipelineStateDescriptor);
		if (!m_PipelineState) {
			return false;
		}

		return true;
	}

	void execute(kyra::RHICommandBuffer::Ptr& commandBuffer, kyra::RPIRenderDataBuffer& buffer) {
		commandBuffer->beginRenderPass(m_RenderPass, nullptr);
		commandBuffer->bindPipeline(m_PipelineState);
		std::vector<TriangleRenderData>& data = buffer.getBuffer<TriangleRenderData>();
		for (auto& renderData : data) {
			commandBuffer->bindVertexBuffer(0, renderData.vertexBuffer);
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

		// Create RHIDevice

		kyra::RHIDevice::Descriptor rhiDeviceDescriptor;
		rhiDeviceDescriptor.window = &window;

		kyra::RHIDevice::Ptr rhiDevice = kyra::RHIDevice::create();
		if (!rhiDevice->init(rhiDeviceDescriptor)) {
			return -2;
		}

		kyra::RHISwapChain::Descriptor swapChainDescriptor;
		swapChainDescriptor.width = 1280;
		swapChainDescriptor.height = 720;

		kyra::RHISwapChain::Ptr swapChain = rhiDevice->createSwapChain(swapChainDescriptor);
		if (!swapChain) {
			return -3;
		}


		kyra::RPIFeatureProcessor::Ptr triangleFeatureProcessor = std::make_unique<TriangleFeature>();
		if (!triangleFeatureProcessor->init(rhiDevice)) {
			return -3;
		}

		kyra::RPIRenderPass::Ptr triangleRenderPass = std::make_unique<TriangleRenderPass>();
		if (!triangleRenderPass->init(rhiDevice)) {
			return -4;
		}

		kyra::RPIRenderPipeline renderPipeline;
		if (!renderPipeline.init(rhiDevice)) {
			return false;
		}
		renderPipeline.registerRenderPass(triangleRenderPass.get());

		kyra::RHICommandQueue::Ptr commandQueue = rhiDevice->createCommandQueue();
		kyra::RHICommandBuffer::Ptr commandBuffer = rhiDevice->createCommandBuffer();

		while (!m_EventHandler.isQuitRequested()) {
			kyra::RPIRenderDataBuffer buffer;
			triangleFeatureProcessor->gather(buffer);
			window->processEvents();
			uint32_t imageIndex = swapChain->acquireNextImage();
			kyra::RHIFrameBuffer* framebuffer = swapChain->getFrameBuffer(imageIndex);
			commandBuffer->begin();
			renderPipeline.renderFrame(buffer,commandBuffer);
			commandBuffer->end();
			commandQueue->submit(commandBuffer);
			swapChain->present(imageIndex);
		}

		return 0;
	}

};

int main(int argc, char** argv) {
	return TestApplication().run(argc, argv);
}