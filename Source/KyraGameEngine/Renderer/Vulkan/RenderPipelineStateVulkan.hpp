#ifndef KYRAGAMEENGINE_RENDERING_OPENGL_RENDERPIPELINESTATEVULKAN_HPP
#define KYRAGAMEENGINE_RENDERING_OPENGL_RENDERPIPELINESTATEVULKAN_HPP

#include <KyraGameEngine/Renderer/RenderPipelineState.hpp>
#include <KyraGameEngine/Math/Matrix4.hpp>
#include <memory>
#include <string>

namespace kyra {


	class RenderPipelineStateVulkan : public RenderPipelineState {

	public:

		void uploadUniform(std::shared_ptr<RenderPipelineState> renderPipeline, const std::string& id, const Matrix4& matrix) {

		}

		bool init(const RenderPipelineStateDescriptor& descriptor) final;
		void bind() final;
	};

}

#endif