#ifndef KYRAGAMEENGINE_RENDERER_RENDERPASS_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPASS_HPP

#include "CommandBuffer.hpp"
#include <vector>
#include <memory>

#include <KyraGameEngine/Core/SystemManager.hpp>

namespace kyra {

	class RenderPass {


	public:
		virtual ~RenderPass() = default;

		virtual void beginDraw(CommandBuffer* commandBuffer) = 0;
		virtual void endDraw(CommandBuffer* commandBuffer) = 0;
		void renderFrame(CommandBuffer* commandBuffer);

	};

}

#endif