#ifndef KYRAGAMEENGINE_RHI_OPENGL_GRAPHICSCONTEXTVULKAN_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_GRAPHICSCONTEXTVULKAN_HPP

#include <KyraGameEngine/RHI/AbstractGraphicsContext.hpp>

namespace kyra {

	class GraphicsContextVulkan : public AbstractGraphicsContext {
		
		public:
	
		static std::unique_ptr<GraphicsContextVulkan> create() {
			return std::make_unique<GraphicsContextVulkan>();
		}
	
		[[nodiscard]] std::unique_ptr<AbstractSwapChain> createSwapChain() final;
	
		[[nodiscard]] std::unique_ptr<AbstractPipeline> createPipeline() final;
		
		[[nodiscard]] std::unique_ptr<AbstractCommandBuffer> createCommandBuffer() final;
		
		[[nodiscard]] std::unique_ptr<AbstractShaderProgram> createShaderProgram() final;
		
		[[nodiscard]] std::unique_ptr<AbstractVertexBuffer> createVertexBuffer() final;

		[[nodiscard]] std::unique_ptr<AbstractRenderPass> createRenderPass() final;
	};
	
	using GraphicsContext = GraphicsContextOpenGL;
}
	
#endif