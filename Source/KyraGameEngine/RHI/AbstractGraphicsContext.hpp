#ifndef KYRAGAMEENGINE_RHI_ABSTRACTGRAPHICSCONTEXT_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTGRAPHICSCONTEXT_HPP

#include "AbstractSwapChain.hpp"
#include "AbstractPipeline.hpp"
#include "AbstractShaderProgram.hpp"
#include "AbstractCommandBuffer.hpp"
#include "AbstractVertexBuffer.hpp"
#include "AbstractRenderPass.hpp"

#include <memory>

namespace kyra {
	
	class AbstractGraphicsContext {
				
		public:
		virtual ~AbstractGraphicsContext() = default;
		
		[[nodiscard]] virtual std::unique_ptr<AbstractSwapChain> createSwapChain() = 0;
		[[nodiscard]] virtual std::unique_ptr<AbstractPipeline> createPipeline() = 0;
		[[nodiscard]] virtual std::unique_ptr<AbstractShaderProgram> createShaderProgram() = 0;
		[[nodiscard]] virtual std::unique_ptr<AbstractCommandBuffer> createCommandBuffer() = 0;
		[[nodiscard]] virtual std::unique_ptr<AbstractVertexBuffer> createVertexBuffer() = 0;
		[[nodiscard]] virtual std::unique_ptr<AbstractRenderPass> createRenderPass() = 0;
	};
	
}

#endif