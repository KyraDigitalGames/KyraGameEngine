#include "RenderPass.hpp"

namespace kyra {

	void RenderPass::renderFrame(CommandBuffer* commandBuffer) {
		beginDraw(commandBuffer);
		endDraw(commandBuffer);
	}

}