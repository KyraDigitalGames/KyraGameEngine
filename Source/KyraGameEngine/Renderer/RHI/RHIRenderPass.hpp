#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHIRENDERPASS_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHIRENDERPASS_HPP

#include <memory>

namespace kyra {

	class RHIRenderPass {

	public:
		virtual ~RHIRenderPass() = default;

		using Ptr = std::unique_ptr<RHIRenderPass>;

		struct Descriptor {

		};

		virtual bool init(const RHIRenderPass::Descriptor& descriptor) = 0;

	};

}

#endif