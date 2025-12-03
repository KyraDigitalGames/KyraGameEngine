#ifndef KYRAGAMEENGINE_RENDERER_RENDERPIPELINE_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERPIPELINE_HPP

#include "RenderPass.hpp"
#include "CommandBuffer.hpp"
#include <vector>
#include <memory>

namespace kyra {

	struct RenderPipelineDescriptor {
		CommandBuffer* commandBuffer = nullptr;
	};

	class RenderPass;
	class RenderPipeline {

		CommandBuffer* m_CommandBuffer = nullptr;
		std::vector<std::shared_ptr<RenderPass>> m_RenderPasses;

	public:

		bool init(const RenderPipelineDescriptor& descriptor);
		
		template<class RenderPassType, class DescriptorType>
		bool registerPass(const DescriptorType& descriptor) {
			m_RenderPasses.emplace_back(std::make_shared<RenderPassType>());
			return static_cast<RenderPassType*>(m_RenderPasses.back().get())->init(descriptor);
		}

		void renderFrame();

	};

}

#endif