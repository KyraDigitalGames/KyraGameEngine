#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIPIPELINELAYOUTOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIPIPELINELAYOUTOPENGL_HPP

#include <KyraGameEngine/Renderer/RHI/RHIPipelineLayout.hpp>

namespace kyra {

	class RHIPipelineLayoutOpenGL : public RHIPipelineLayout {

	public:

		bool init(const RHIPipelineLayout::Descriptor& descriptor) final {
			return true;
		}
	
	};


}

#endif