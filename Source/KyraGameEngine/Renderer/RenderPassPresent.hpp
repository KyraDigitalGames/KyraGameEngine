#ifndef KYRAGAMEENGINE_RENDERER_RENDERPASSPRESENT_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPASSPRESENT_HPP

#include "RenderPass.hpp"
#include "Swapchain.hpp"
#include "RenderPassProcessor.hpp"

namespace kyra {

	struct RenderPassPresentDescriptor {
		Swapchain* swapchain = nullptr;
		std::shared_ptr<RenderPassProcessor> processor = nullptr;
	};

	class RenderPassPresent : public RenderPass {

		Swapchain* m_Swapchain = nullptr;
		std::shared_ptr<RenderPassProcessor> m_Processor = nullptr;

	public:

		bool init(const RenderPassPresentDescriptor& descriptor);

		void beginDraw(CommandBuffer* commandBuffer);

		void endDraw(CommandBuffer* commandBuffer);

	};

}

#endif