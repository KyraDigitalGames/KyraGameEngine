#ifndef KYRAGAMEENGINE_RENDERER_COMMANDBUFFER_HPP
#define KYRAGAMEENGINE_RENDERER_COMMANDBUFFER_HPP

#include "VertexBuffer.hpp"
#include "RenderPipelineState.hpp"
#include "Texture.hpp"
#include <memory>
#include <string>


namespace kyra {

	class CommandBuffer {

	public:
		virtual ~CommandBuffer() = default;

		virtual void clear(float r, float g, float b, float a) = 0;
		virtual void bindVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
		virtual void updateBuffer(std::shared_ptr<VertexBuffer> vertexBuffer, const VertexBufferDescriptor& descriptor) = 0;
		virtual void bindRenderPipelineState(std::shared_ptr<RenderPipelineState> renderPipelineState) = 0;
		virtual void bindTexture(Texture* texture) = 0;
		virtual void setUniformMat4(std::shared_ptr<RenderPipelineState> renderPipeline, const std::string& id, const Matrix4& matrix) = 0;
		virtual void draw(std::size_t offset, std::size_t count) = 0;
	};

}

#endif