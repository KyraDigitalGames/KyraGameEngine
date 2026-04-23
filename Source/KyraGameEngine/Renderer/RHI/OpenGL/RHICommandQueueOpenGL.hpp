#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHICOMMANDBUFFEROPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHICOMMANDBUFFEROPENGL_HPP

#include <KyraGameEngine/Renderer/RHI/RHICommandBuffer.hpp>

namespace kyra {

	class RHICommandQueueOpenGL : public RHICommandQueue {

	public:
		virtual ~RHICommandQueueOpenGL() = default;


		virtual void submit(RHICommandBuffer::Ptr& buffer) {

		}
	};


}

#endif