#include "RenderPassPresent.hpp"

namespace kyra {

	bool RenderPassPresent::init(const RenderPassPresentDescriptor& descriptor) {
		if (!descriptor.swapchain) {
			return false;
		}
		m_Swapchain = descriptor.swapchain;
		m_Processor = descriptor.processor;
		return true;
	}

	void RenderPassPresent::beginDraw(CommandBuffer* commandBuffer) {
		commandBuffer->clear(0, 0, 0, 0);
		if (m_Processor) {
			m_Processor->update(commandBuffer);
		}
	}

	void RenderPassPresent::endDraw(CommandBuffer* commandBuffer) {
		m_Swapchain->swap();
	}

}