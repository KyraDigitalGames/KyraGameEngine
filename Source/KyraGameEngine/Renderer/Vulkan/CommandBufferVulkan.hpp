#ifndef KYRAGAMEENGINE_RENDERER_COMMANDBUFFERVULKAN_HPP
#define KYRAGAMEENGINE_RENDERER_COMMANDBUFFERVULKAN_HPP

#include <KyraGameEngine/Renderer/CommandBuffer.hpp>
#include <memory>

namespace kyra {

	class CommandBufferVulkan : public CommandBuffer {

	public:

		void clear(float r, float g, float b, float a) final;
		void bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer) final;
		void bindRenderPipelineState(std::shared_ptr<RenderPipelineState> renderPipelineState) final;
		void setUniformMat4(std::shared_ptr<RenderPipelineState> renderPipeline, const std::string& id, const Matrix4& matrix) final;
		void draw(std::size_t offset, std::size_t count) final;

	};

}

#endif