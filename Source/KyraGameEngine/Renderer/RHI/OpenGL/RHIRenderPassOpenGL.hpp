#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIREMDERPASSOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIRENDERPASSOPENGL_HPP

#include <KyraGameEngine/Renderer/RHI/RHIRenderPass.hpp>

namespace kyra {

	class RHIRenderPassOpenGL : public RHIRenderPass {

	public:
		virtual ~RHIRenderPassOpenGL() = default;

		virtual bool init(const RHIRenderPass::Descriptor& descriptor) final {
			return true;
		}

	};

}

#endif