
#include "GraphicsContextOpenGL.hpp"
#include "SwapChainOpenGL.hpp"
#include "PipelineOpenGL.hpp"
#include "ShaderProgramOpenGL.hpp"
#include "VertexBufferOpenGL.hpp"
#include "CommandBufferOpenGL.hpp"
#include "RenderPassOpenGL.hpp"


namespace kyra {

	std::unique_ptr<AbstractSwapChain> GraphicsContextOpenGL::createSwapChain() {
		return std::make_unique<SwapChainOpenGL>();
	}
	
	std::unique_ptr<AbstractPipeline> GraphicsContextOpenGL::createPipeline() {
		return std::make_unique<PipelineOpenGL>();
	}
		
	std::unique_ptr<AbstractCommandBuffer> GraphicsContextOpenGL::createCommandBuffer() {
		return std::make_unique<CommandBufferOpenGL>();
	}
		
	std::unique_ptr<AbstractShaderProgram> GraphicsContextOpenGL::createShaderProgram() {
		return std::make_unique<ShaderProgramOpenGL>();
	}
		
	std::unique_ptr<AbstractVertexBuffer> GraphicsContextOpenGL::createVertexBuffer() {
		return std::make_unique<VertexBufferOpenGL>();
	}

	std::unique_ptr<AbstractRenderPass> GraphicsContextOpenGL::createRenderPass() {
		return std::make_unique<RenderPassOpenGL>();
	}

}
	
