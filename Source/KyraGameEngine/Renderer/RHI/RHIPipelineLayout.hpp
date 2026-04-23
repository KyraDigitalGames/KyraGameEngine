#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHIPIPELINELAYOUT_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHIPIPELINELAYOUT_HPP

#include <memory>

namespace kyra {

	class RHIPipelineLayout {

	public:
		virtual ~RHIPipelineLayout() = default;

		using Ptr = std::unique_ptr<RHIPipelineLayout>;

		struct Descriptor {

		};

		virtual bool init(const RHIPipelineLayout::Descriptor& descriptor) = 0;

	};


}

#endif