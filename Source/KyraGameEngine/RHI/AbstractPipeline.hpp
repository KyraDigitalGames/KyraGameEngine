#ifndef KYRAGAMEENGINE_RHI_ABSTRACTPIPELINE_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTPIPELINE_HPP

#include "AbstractShaderProgram.hpp"
#include "BufferLayout.hpp"
#include "DescriptorSet.hpp"
#include <array>

namespace kyra {
	
	struct PipelineDescriptor {
		AbstractShaderProgram* shaderProgram = nullptr;
		BufferLayout bufferLayout;
		std::array<DescriptorSet*,3> descriptorSetArray;
	};
	
	class AbstractPipeline {
		
		public:
		virtual ~AbstractPipeline() = default;
		
		[[nodiscard]] virtual bool init(const PipelineDescriptor& pipeline) = 0;
		virtual void bind() = 0;
	};
}

#endif