#include "CommandBufferVulkan.hpp"

namespace kyra {

	void CommandBufferVulkan::clear(float r, float g, float b, float a) {

	}

	void CommandBufferVulkan::bindVertexBuffer(std::shared_ptr<VertexBuffer> buffer) {

	}

	void CommandBufferVulkan::bindRenderPipelineState(std::shared_ptr<RenderPipelineState> renderPipelineState) {
		renderPipelineState->bind();
	}

	void CommandBufferVulkan::draw(std::size_t offset, std::size_t count) {

	}


	void CommandBufferVulkan::setUniformMat4(std::shared_ptr<RenderPipelineState> renderPipeline, const std::string& id, const Matrix4& matrix) {

	}



}