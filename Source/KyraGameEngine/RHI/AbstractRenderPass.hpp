#ifndef KYRAGAMEENGINE_RHI_ABSTRACTRENDERPASS_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTRENDERPASS_HPP

#include "AbstractRenderTarget.hpp"
#include "AbstractCommandBuffer.hpp"
#include "AbstractDescriptorSet.hpp"

namespace kyra {
	
	class AbstractRenderPass {
		
		public:
		virtual ~AbstractRenderPass() = default;
		
		virtual void begin(AbstractCommandBuffer* commandBuffer, 
						   AbstractRenderTarget* renderTarget) = 0;
		virtual void end() = 0;
				
	};
}

#endif