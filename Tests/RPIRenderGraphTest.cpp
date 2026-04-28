
#include <KyraGameEngine/Window/WindowEvent.hpp>
#include <KyraGameEngine/Window/Windows/WindowWindows.hpp>
#include <KyraGameEngine/Renderer/RHI/RHIDevice.hpp>

#include <string>
#include <unordered_map>
#include <typeindex>

namespace kyra {


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

	class RPIRenderView {

	};

	class RPIRenderPass {

	public:
		virtual ~RPIRenderPass() = default;

		using Ptr = std::unique_ptr<RPIRenderPass>;

		virtual void execute(RPIRenderDataBuffer& renderData) {

		}

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

		void execute(RPIRenderDataBuffer& renderData) {
			if (m_RenderPasses.empty()) {
				return;
			}
			for (auto& renderPass : m_RenderPasses) {
				renderPass->execute(renderData);
			}
		}

		void reset() {
			m_RenderPasses.clear();
		}

	};

}

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
			return false;
		}

		std::vector<kyra::RPIRenderPass::Ptr> renderPasses;

		kyra::RHICommandQueue::Ptr commandQueue = renderDevice->createCommandQueue();
		kyra::RHICommandBuffer::Ptr commandBuffer = renderDevice->createCommandBuffer();

		kyra::RPIRenderGraph renderGraph;
		kyra::RPIRenderDataBuffer renderData;

		while(!m_EventHandler.isQuitRequested()) {

			window->processEvents();

			kyra::RHICommandQueue::Ptr commandQueue = renderDevice->createCommandQueue();
			kyra::RHICommandBuffer::Ptr commandBuffer = renderDevice->createCommandBuffer();
			uint32_t imageIndex = m_SwapChain->acquireNextImage();
			kyra::RHIFrameBuffer* framebuffer = m_SwapChain->getFrameBuffer(imageIndex);


			renderGraph.compile(renderPasses);
			renderGraph.execute(renderData);
			renderGraph.reset();
			//
			//renderGraph.compile(renderPasses);
			//renderGraph.execute(commandBuffer.get());

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