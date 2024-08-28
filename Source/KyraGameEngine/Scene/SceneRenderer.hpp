#ifndef KYRAGAMEENGINE_SCENE_SCENERENDERER_HPP
#define KYRAGAMEENGINE_SCENE_SCENERENDERER_HPP

#include "Scene.hpp"
#include <KyraGameEngine/Graphics/RenderCommand2D.hpp>

#include <vector>
#include <iostream>

namespace kyra {
		
	class SceneRenderer {
		
		std::vector<RenderCommand2D> m_RenderCommands2D;
		AbstractGraphicsContext* m_Context = nullptr;
		
		std::unique_ptr<AbstractPipeline> m_SpritePipeline;
		std::unique_ptr<AbstractShaderProgram> m_SpriteShaderProgram;
		std::unique_ptr<AbstractVertexBuffer> m_SpriteVertexBuffer;		
				
		public:
		
		bool init(AbstractGraphicsContext* context) {
			
			if(!context) {
				return false;
			}
			
			ShaderDescriptionGLSL shaderDescription;
			shaderDescription.vertexShader = "./Assets/Shaders/SpriteShader.vs";
			shaderDescription.fragmentShader = "./Assets/Shaders/SpriteShader.fs";
			m_SpriteShaderProgram = context->createShaderProgram();
			if(!m_SpriteShaderProgram->init(shaderDescription)) {
				return false;
			}
			
			PipelineDescriptor pipelineDescriptor;
			pipelineDescriptor.shaderProgram = m_SpriteShaderProgram.get();
			pipelineDescriptor.bufferLayout.add<float>("aPos", 2, false);
			pipelineDescriptor.bufferLayout.add<float>("aColor", 4, false);
			pipelineDescriptor.bufferLayout.add<float>("aUV", 2, false);
			m_SpritePipeline = context->createPipeline();
			if(!m_SpritePipeline->init(pipelineDescriptor)) {
				return false;
			}
			
			m_SpriteVertexBuffer = context->createVertexBuffer();
			m_SpriteVertexBuffer->setData( 30 * sizeof(SpriteVertex), nullptr );
			
			return true;
		}
		
		void draw(AbstractCommandBuffer* commandBuffer, Scene* scene) {
			
			for(auto sprite : scene->getSprites()) {
				RenderCommand2D renderCommand2D;
				renderCommand2D.renderable = sprite; 
				m_RenderCommands2D.push_back(renderCommand2D);
			}
					
			std::size_t offset = 0;
			std::size_t bufferIndex = 0;
			std::size_t elementIndex = 0;
			
			commandBuffer->bindPipeline(m_SpritePipeline.get());
			commandBuffer->bindVertexBuffer(m_SpriteVertexBuffer.get());
			
			for(auto renderCommand : m_RenderCommands2D) {
				if(offset+renderCommand.renderable->getSize() > m_SpriteVertexBuffer->getSize()) {
					commandBuffer->draw(0, elementIndex);
					elementIndex = 0;
					bufferIndex = 0;
				} 
				m_SpriteVertexBuffer->setSubData(renderCommand.renderable->getSize(), renderCommand.renderable->getDataPtr(), bufferIndex);
				bufferIndex += renderCommand.renderable->getSize(); 
				elementIndex += renderCommand.renderable->getElementCount();
			}
			if(elementIndex > 0) {
				commandBuffer->draw(0, elementIndex);	
			}
			
			m_RenderCommands2D.clear();
		}
		
	};
}

#endif