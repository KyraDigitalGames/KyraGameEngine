
#include <KyraGameEngine/Window/WindowEvent.hpp>
#include <KyraGameEngine/Window/Windows/WindowWindows.hpp>
#include <KyraGameEngine/Renderer/RHI/RHIDevice.hpp>

#include <iostream>


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

		// Create window

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

		// Create SwapChain

		kyra::RHISwapChain::Descriptor swapChainDescriptor;
		swapChainDescriptor.width = 1280;
		swapChainDescriptor.height = 720;
		
		kyra::RHISwapChain::Ptr swapChain = rhiDevice->createSwapChain(swapChainDescriptor);
		if (!swapChain) {
			return -3;
		}

		
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
		kyra::RHIShader::Ptr vertexShader = rhiDevice->createShader(vertexShaderDescriptor);
		if (!vertexShader) {
			return -4;
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
		kyra::RHIShader::Ptr fragmentShader = rhiDevice->createShader(fragmentShaderDescriptor);
		if (!fragmentShader) {
			return -5;
		}

		kyra::RHIPipelineLayout::Descriptor pipelineLayoutDescriptor;
		kyra::RHIPipelineLayout::Ptr pipelineLayout = rhiDevice->createPipelineLayout(pipelineLayoutDescriptor);
		if (!pipelineLayout) {
			return -6;
		}

		kyra::RHIRenderPass::Descriptor renderPassDescriptor;
		kyra::RHIRenderPass::Ptr renderPass = rhiDevice->createRenderPass(renderPassDescriptor);
		if (!renderPass) {
			return -7;
		}

		struct Vertex {
			float position[3];
			float color[3];
		};

		kyra::RHIPipelineState::Descriptor pipelineStateDescriptor;
		pipelineStateDescriptor.fragmentShader = &fragmentShader;
		pipelineStateDescriptor.vertexShader = &vertexShader;
		pipelineStateDescriptor.renderPass = &renderPass;
		pipelineStateDescriptor.pipelineLayout = &pipelineLayout;
		pipelineStateDescriptor.bufferLayout.stride = sizeof(Vertex);
		pipelineStateDescriptor.bufferLayout.attributes = {
			{0, kyra::RHIPipelineState::BufferLayoutAttribute::Format::Float, 3, 0},
			{1, kyra::RHIPipelineState::BufferLayoutAttribute::Format::Float, 3, 3 * sizeof(float)}
		};
		kyra::RHIPipelineState::Ptr pipelineState = rhiDevice->createPipelineState(pipelineStateDescriptor);
		if (!pipelineState) {
			return -8;
		}

		// Create command buffer and command queue

		kyra::RHICommandQueue::Ptr commandQueue = rhiDevice->createCommandQueue();
		kyra::RHICommandBuffer::Ptr commandBuffer = rhiDevice->createCommandBuffer();

		// Create Vertex Buffer
		Vertex vertices[] = {
			{{0,0.5,0}, {1,0,0}},
			{{-0.5,-0.5,0}, {0,1,0}},
			{{0.5,-0.5,0}, {0,0,1}}
		};

		kyra::RHIBuffer::Descriptor vertexBufferDescriptor;
		vertexBufferDescriptor.size = sizeof(vertices);
		vertexBufferDescriptor.usage = kyra::RHIBuffer::Type::Vertex;
		kyra::RHIBuffer::Ptr vertexBuffer = rhiDevice->createBuffer(vertexBufferDescriptor);
		if (!vertexBuffer) {
			return -8;
		}
		vertexBuffer->upload(vertices, sizeof(vertices));

		// Run main loop

		while (!m_EventHandler.isQuitRequested()) {
			window->processEvents();
			uint32_t imageIndex = swapChain->acquireNextImage();
			kyra::RHIFrameBuffer* framebuffer = swapChain->getFrameBuffer(imageIndex);
			
			commandBuffer->begin();
				commandBuffer->beginRenderPass(renderPass, framebuffer);
					commandBuffer->bindPipeline(pipelineState);
					commandBuffer->bindVertexBuffer(0, vertexBuffer);
					commandBuffer->draw(0, 3);
				commandBuffer->endRenderPass();
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