#include "RenderPipeline.hpp"

namespace kyra {
	
	bool RenderPipeline::init(const RenderPipelineDescriptor& descriptor) {
		m_CommandBuffer = descriptor.commandBuffer;
		return true;
	}

	void RenderPipeline::renderFrame() {
		for (auto& renderPass : m_RenderPasses) {
			renderPass->renderFrame(m_CommandBuffer);
		}
	}

}