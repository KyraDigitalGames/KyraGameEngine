#ifndef KYRAGAMEENGINE_RHI_OPENGL_RENDERPASSOPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_RENDERPASSOPENGL_HPP

#include <KyraGameEngine/RHI/AbstractRenderPass.hpp>

namespace kyra {
	
	class RenderPassOpenGL : public AbstractRenderPass {
		
		public:
		
		void begin(AbstractCommandBuffer* commandBuffer, AbstractRenderTarget* renderTarget) final {
			commandBuffer->clear();	
		}
		
		void end() final {
			
		}
				
	};
}

#endif