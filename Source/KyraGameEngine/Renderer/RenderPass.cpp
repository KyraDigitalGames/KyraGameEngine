#include "RenderPass.hpp"
#include <KyraGameEngine/Debug/Profiling.hpp>

namespace kyra {

	void RenderPass::renderFrame(CommandBuffer* commandBuffer) {
		KYRA_PROFILE_FUNCTION();
		beginDraw(commandBuffer);
		endDraw(commandBuffer);
	}

}