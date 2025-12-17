#ifndef KYRAGAMEENGINE_RENDERER_RENDERPASS_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPASS_HPP

#include "CommandBuffer.hpp"
#include <vector>
#include <memory>

#include <KyraGameEngine/Core/SystemManager.hpp>
#include <KyraGameEngine/GameModule/GameModule.hpp>
#include "RenderPassProcessor.hpp"
#include "Swapchain.hpp"
#include "CommandBuffer.hpp"

namespace kyra {

	struct RenderPassDescriptor {
		Swapchain* swapchain = nullptr;
		CommandBuffer* commandBuffer = nullptr;
		std::vector<std::string> processorNames;
		SystemManager* systemManager = nullptr;
		Registry<RenderPassProcessor>* processorRegistry = nullptr;
		Renderer* renderer = nullptr;
	};

	class RenderPass {


	public:
		virtual ~RenderPass() = default;

		virtual bool init(const RenderPassDescriptor& descriptor) = 0;

		virtual void beginDraw(CommandBuffer* commandBuffer) = 0;
		virtual void endDraw(CommandBuffer* commandBuffer) = 0;
		void renderFrame(CommandBuffer* commandBuffer);

		

		std::size_t getHash() const {
			return typeid(RenderPass).hash_code();
		}

		template<class RenderPassType>
		RenderPassType* toType() {
			return static_cast<RenderPassType*>(this);
		}

	};

}

#endif