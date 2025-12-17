#include "RenderPassPresent.hpp"
#include <KyraGameEngine/Debug/Profiling.hpp>

namespace kyra {

	bool RenderPassPresent::init(const RenderPassDescriptor& descriptor) {
		KYRA_PROFILE_FUNCTION();
		if (!descriptor.swapchain) {
			return false;
		}
		m_Swapchain = descriptor.swapchain;
		for(auto& processorName : descriptor.processorNames) {
			auto processor = descriptor.processorRegistry->create(processorName);
			if (processor) {
				processor->setSystemManager(descriptor.systemManager);
				if (!processor->init( *descriptor.renderer)) {
					return false;
				}
				m_Processors.emplace_back(processor);
			}
		}
		return true;
	}

	void RenderPassPresent::beginDraw(CommandBuffer* commandBuffer) {
		KYRA_PROFILE_FUNCTION();
		commandBuffer->clear(0, 0, 0, 0);
		for(auto& processor : m_Processors) {
			processor->update(commandBuffer);
		}
	}

	void RenderPassPresent::endDraw(CommandBuffer* commandBuffer) {
		KYRA_PROFILE_FUNCTION();
		if (m_Swapchain) {
			m_Swapchain->swap();

		}
	}

}