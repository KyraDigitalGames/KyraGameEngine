#ifndef KYRAGAMEENGINE_SCENE_2D_SCENERENDERPASSPROCESSOR2D_HPP
#define KYRAGAMEENGINE_SCENE_2D_SCENERENDERPASSPROCESSOR2D_HPP

#include <KyraGameEngine/Renderer/RenderPassProcessor.hpp>
#include <KyraGameEngine/Renderer/Renderer.hpp>
#include <KyraGameEngine/Math/Matrix4.hpp>
#include <memory>


namespace kyra {

	class SceneRenderPassProcessor2D : public kyra::RenderPassProcessor {

		std::shared_ptr<kyra::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<kyra::RenderPipelineState> m_RenderPipelineState;
		kyra::Matrix4 m_Projection;

	public:

		bool init(kyra::Renderer& renderer) final {

			const auto windowSize = getSystem<kyra::Window>()->getSize();
			m_Projection = kyra::Matrix4::ortho(0, windowSize.getX(), windowSize.getY(), 0, -1, 1);

			float vertices[] = {
				0,0,0,0,
				1,0,1,0,
				1,1,1,1,
				0,0,0,0,
				0,1,0,1,
				1,1,0,0
			};


			kyra::VertexBufferDescriptor vertexBufferDescriptor;
			vertexBufferDescriptor.size = 24 * sizeof(float);
			vertexBufferDescriptor.data = vertices;
			m_VertexBuffer = renderer.createVertexBuffer();
			if (!m_VertexBuffer->init(vertexBufferDescriptor)) {
				return false;
			}

			kyra::ShaderDescriptor vertexShader;
			vertexShader.type = kyra::ShaderType::Vertex;
			vertexShader.language = kyra::ShaderLanguage::GLSL;
			vertexShader.data = "#version 330 core\n"
				"layout (location = 0) in vec2 aPos;\n"
				"layout (location = 1) in vec2 aUV;\n"
				"uniform mat4 m_Projection;\n"
				"uniform mat4 m_Model;\n"
				"out vec2 oUV;\n"
				"void main() {\n"
				"oUV = aUV;\n"
				"gl_Position = m_Projection * m_Model * vec4(aPos.x, aPos.y, 0.0,  1.0);\n"
				"}\0";

			kyra::ShaderDescriptor fragmentShader;
			fragmentShader.type = kyra::ShaderType::Fragment;
			fragmentShader.language = kyra::ShaderLanguage::GLSL;
			fragmentShader.data = "#version 330 core\n"
				"in vec2 oUV;\n"
				"out vec4 FragColor;\n"
				"uniform sampler2D ourTexture;\n"
				"void main() {\n"
				"FragColor = texture(ourTexture, oUV);\n"
				"}\0";;

			kyra::RenderPipelineStateDescriptor renderPipelineStateDescriptor;
			renderPipelineStateDescriptor.shaders.emplace_back(vertexShader);
			renderPipelineStateDescriptor.shaders.emplace_back(fragmentShader);
			m_RenderPipelineState = renderer.createRenderPipelineState();
			if (!m_RenderPipelineState->init(renderPipelineStateDescriptor)) {
				return false;
			}

			return true;
		}

		void update(kyra::CommandBuffer* commandBuffer) final {
			commandBuffer->bindVertexBuffer(m_VertexBuffer);
			commandBuffer->bindRenderPipelineState(m_RenderPipelineState);
			auto simpleMeshSystem = getSystem<kyra::SceneSystem2D>();
			for (auto& component : simpleMeshSystem->getSpriteComponents()) {
				commandBuffer->setUniformMat4(m_RenderPipelineState, "m_Projection", m_Projection);
				commandBuffer->setUniformMat4(m_RenderPipelineState, "m_Model", component->getTransform());
				commandBuffer->bindTexture(component->getTexture());
				commandBuffer->draw(0, 6);
			}
		}

	};

}

#endif