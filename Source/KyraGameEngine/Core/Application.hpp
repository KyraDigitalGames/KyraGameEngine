#ifndef KYRAGAMEENGINE_CORE_APPLICATION_HPP
#define KYRAGAMEENGINE_CORE_APPLICATION_HPP

#include <KyraGameEngine/Platform/Windows/WindowWinAPI.hpp>

/*#define KYRA_PLATFORM_WINDOWS
#include <KyraGameEngine/Windows.hpp>

#define KYRA_RENDERER_OPENGL
#include <KyraGameEngine/RHI.hpp>*/

#include <KyraGameEngine/RHI/OpenGL/GraphicsContextOpenGL.hpp>
#include <KyraGameEngine/Graphics/Vertex2D.hpp>
#include <KyraGameEngine/Graphics/Sprite.hpp>
#include <KyraGameEngine/Graphics/RenderCommand2D.hpp>
#include <KyraGameEngine/Scene/SceneRenderer.hpp>


namespace kyra {
	
	class Image {
		
		public:
		
	};
	
	class Application {
	
		virtual bool onInit(WindowDescriptor& windowDescriptor) = 0;
			
		public:
		virtual ~Application() = default;
		
		int run(int argc, char** argv) {
			
			WindowDescriptor windowDescriptor;
			if(!onInit(windowDescriptor)) {
				return -1;
			}
			
			auto window = std::make_unique<Window>();
			if(!window->init(windowDescriptor)) {
				return -2;
			}
			
			auto graphicsContext = std::make_unique<GraphicsContextOpenGL>();
						
			SwapChainDescriptor swapChainDescriptor;
			swapChainDescriptor.window = window.get();
			
			auto swapChain = graphicsContext->createSwapChain();
			if(!swapChain->init(swapChainDescriptor)) {
				return false;
			}
			
			/*ShaderDescriptionGLSL shaderDescription;
			shaderDescription.vertexShader = "./Assets/Shaders/SpriteShader.vs";
			shaderDescription.fragmentShader = "./Assets/Shaders/SpriteShader.fs";
			auto spriteShader = graphicsContext->createShaderProgram();
			if(!spriteShader->init(shaderDescription)) {
				return false;
			}
			
			PipelineDescriptor pipelineDescriptor;
			pipelineDescriptor.shaderProgram = spriteShader.get();
			pipelineDescriptor.bufferLayout.add<float>("aPos", 2, false);
			pipelineDescriptor.bufferLayout.add<float>("aColor", 4, false);
			pipelineDescriptor.bufferLayout.add<float>("aUV", 2, false);
			auto pipeline = graphicsContext->createPipeline();
			if(!pipeline->init(pipelineDescriptor)) {
				return false;
			}
			
			float vertices[] = {
				-0.5f, -0.5f, 0, 0, 1, 1, 0,0,
				0.0f, 0.5f, 0,1,0,1,0,0,
				0.5f, -0.5f, 1,0,0,1,0,0
			};
			
			auto vertexBuffer = graphicsContext->createVertexBuffer();
			vertexBuffer->setData( sizeof(vertices), &vertices[0] );*/
						
			auto commandBuffer = graphicsContext->createCommandBuffer();
								
			AbstractRenderTarget renderTarget;
			
			auto renderPass = graphicsContext->createRenderPass();
			
			std::unique_ptr<SceneRenderer> sceneRenderer = std::make_unique<SceneRenderer>();
			if(!sceneRenderer->init(graphicsContext.get())) {
				return false;
			} 
			
			Sprite sprite;
			
			Scene defaultScene;
			defaultScene.addSprite(&sprite);
			
			while(window->isOpen()) {
				window->processEvents();
				renderPass->begin(commandBuffer.get(), &renderTarget);
				//commandBuffer->bindPipeline(pipeline.get());
				//commandBuffer->bindVertexBuffer(vertexBuffer.get());
				//commandBuffer->draw(0,3);
				sceneRenderer->draw(commandBuffer.get(), &defaultScene);
				renderPass->end();
				swapChain->present();
			}
			
			sceneRenderer.reset();
			swapChain.reset();
			window.reset();
			
			return 0;
		}
		
	};
	
}

#endif