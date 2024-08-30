#include <KyraGameEngine/Platform.hpp>
#include <KyraGameEngine/RHI.hpp>

int main(int argc, char** argv) {
	
	// Create window
	
	kyra::WindowDescriptor windowDescriptor;
	windowDescriptor.title = "Kyra Game Engine";
	windowDescriptor.width = 1280;
	windowDescriptor.height = 720;
			
	auto window = kyra::Window::create();
	if(!window->init(windowDescriptor)) {
		return -1;
	}
	
	// Create graphics context
	auto graphicsContext = kyra::GraphicsContext::create();
						
	// Create swap chain					
						
	kyra::SwapChainDescriptor swapChainDescriptor;
	swapChainDescriptor.window = window.get();
			
	auto swapChain = graphicsContext->createSwapChain();
	if(!swapChain->init(swapChainDescriptor)) {
		return false;
	}
	
	// Create shader program
	
	kyra::ShaderDescriptionGLSL shaderDescription;
	shaderDescription.vertexShader = "../Assets/Shaders/SpriteShader.vs";
	shaderDescription.fragmentShader = "../Assets/Shaders/SpriteShader.fs";
	auto spriteShader = graphicsContext->createShaderProgram();
	if(!spriteShader->init(shaderDescription)) {
		return false;
	}
	
	// Create pipeline 
			
	kyra::PipelineDescriptor pipelineDescriptor;
	pipelineDescriptor.shaderProgram = spriteShader.get();
	pipelineDescriptor.bufferLayout.add<float>("aPos", 2, false);
	pipelineDescriptor.bufferLayout.add<float>("aColor", 4, false);
	pipelineDescriptor.bufferLayout.add<float>("aUV", 2, false);
	auto pipeline = graphicsContext->createPipeline();
	if(!pipeline->init(pipelineDescriptor)) {
		return false;
	}
			
	float vertices[] = {
		0.5f, 0.5f, 0, 0, 1, 1, 0,0,
		-0.5f, 0.5f, 0,1,0,1,0,0,
		-0.5f, -0.5f, 1,0,0,1,0,0,
		0.5f, 0.5f, 0,0,1,1,0,0,
		0.5f, -0.5f, 0,1,0,1,0,0,
		-0.5f, -0.5f, 1,0,0,1,0,0
	};
			
	auto vertexBuffer = graphicsContext->createVertexBuffer();
	vertexBuffer->setData( sizeof(vertices), &vertices[0] );
						
	auto commandBuffer = graphicsContext->createCommandBuffer();
	auto renderPass = graphicsContext->createRenderPass();
	kyra::AbstractRenderTarget renderTarget;
	
	window->show();
	while(window->isOpen()) {
		window->processEvents();
		renderPass->begin(commandBuffer.get(), &renderTarget);
		commandBuffer->bindPipeline(pipeline.get());
		commandBuffer->bindVertexBuffer(vertexBuffer.get());
		commandBuffer->draw(0,6);
		renderPass->end();
		swapChain->present();
	}
				
	return 0;
}
