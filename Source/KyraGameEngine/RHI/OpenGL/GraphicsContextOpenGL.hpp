#ifndef KYRAGAMEENGINE_RHI_OPENGL_GRAPHICSCONTEXTOPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_GRAPHICSCONTEXTOPENGL_HPP

#include <KyraGameEngine/RHI/AbstractGraphicsContext.hpp>
#include <memory>

namespace kyra {

	class GraphicsContextOpenGL : public AbstractGraphicsContext {
		
		public:
	
		static std::unique_ptr<GraphicsContextOpenGL> create() {
			return std::make_unique<GraphicsContextOpenGL>();
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