#ifndef KYRAGAMEENGINE_RENDERER_COMMANDBUFFEROPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_COMMANDBUFFEROPENGL_HPP

#include <KyraGameEngine/Renderer/CommandBuffer.hpp>
#include <map>

namespace kyra {

	class CommandBufferOpenGL : public CommandBuffer {

		std::shared_ptr<VertexBuffer> m_BoundVertexBuffer;
		std::shared_ptr<RenderPipelineState> m_BoundRenderPipelineState;

	public:

		void clear(float r, float g, float b, float a) final;
		void bindVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
		void updateBuffer(std::shared_ptr<VertexBuffer> vertexBuffer, const VertexBufferDescriptor& descriptor);
		void bindRenderPipelineState(std::shared_ptr<RenderPipelineState> renderPipelineState);
		void bindTexture(Texture* texture);
		void draw(std::size_t offset, std::size_t count) final;
		void setUniformMat4(std::shared_ptr<RenderPipelineState> renderPipeline, const std::string& id, const Matrix4& matrix) final;

	};

}

#endif