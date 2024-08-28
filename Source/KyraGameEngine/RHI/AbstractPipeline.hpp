#ifndef KYRAGAMEENGINE_RHI_ABSTRACTPIPELINE_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTPIPELINE_HPP

#include "AbstractShaderProgram.hpp"
#include "BufferLayout.hpp"

namespace kyra {
	
	struct PipelineDescriptor {
		AbstractShaderProgram* shaderProgram = nullptr;
		BufferLayout bufferLayout;
	};
	
	class AbstractPipeline {
		
		public:
		virtual ~AbstractPipeline() = default;
		
		[[nodiscard]] virtual bool init(const PipelineDescriptor& pipeline) = 0;
		virtual void bind() = 0;
	};
}

#endif