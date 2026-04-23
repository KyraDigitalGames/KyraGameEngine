#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHIPIPELINESTATE_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHIPIPELINESTATE_HPP

#include "RHIShader.hpp"
#include "RHIPipelineLayout.hpp"
#include "RHIRenderPass.hpp"
#include <memory>
#include <vector>

namespace kyra {

	class RHIPipelineState {

	public:
		virtual ~RHIPipelineState() = default;

		using Ptr = std::unique_ptr<RHIPipelineState>;


		struct BufferLayoutAttribute {
			enum class Format {
				Float
			};
			int id = 0;
			Format format = Format::Float;
			std::size_t elements;
			std::size_t offset;
		};

		struct BufferLayout {
			std::size_t stride;
			std::vector<BufferLayoutAttribute> attributes;
		};

		struct Descriptor {
			RHIShader::Ptr* vertexShader;
			RHIShader::Ptr* fragmentShader;
			RHIPipelineLayout::Ptr* pipelineLayout;
			RHIRenderPass::Ptr* renderPass;
			BufferLayout bufferLayout;
		};

		virtual bool init(const RHIPipelineState::Descriptor& descriptor) = 0;


	};

}

#endif