#ifndef KYRAGAMEENGINE_RENDERER_RENDERPASSPRESENT_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPASSPRESENT_HPP

#include "RenderPass.hpp"
#include "Swapchain.hpp"
#include "RenderPassProcessor.hpp"
#include <KyraGameEngine/Log/Logger.hpp>

namespace kyra {


	class RenderPassPresent : public RenderPass {

		Swapchain* m_Swapchain = nullptr;
		std::vector<std::shared_ptr<RenderPassProcessor>> m_Processors;

	public:
		RenderPassPresent() {
			KYRA_LOG_INFO("Creating RenderPassPresent");
		}

		~RenderPassPresent() override {
			KYRA_LOG_INFO("Destroying RenderPassPresent");
		}

		bool init(const RenderPassDescriptor& descriptor);

		void beginDraw(CommandBuffer* commandBuffer);

		void endDraw(CommandBuffer* commandBuffer);

	};

}

#endif