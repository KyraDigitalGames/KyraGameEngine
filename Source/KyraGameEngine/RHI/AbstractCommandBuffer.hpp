#ifndef KYRAGAMEENGINE_RHI_ABSTRACTCOMMANDBUFFER_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTCOMMANDBUFFER_HPP

#include "AbstractPipeline.hpp"
#include "AbstractVertexBuffer.hpp"
#include "AbstractDescriptorSet.hpp"

namespace kyra {
	
	class AbstractCommandBuffer {
		
		public:
		virtual ~AbstractCommandBuffer() = default;
		
		virtual void clear() = 0;
		virtual void bindPipeline(AbstractPipeline* pipeline) = 0;
		virtual void bindVertexBuffer(AbstractVertexBuffer* vertexBuffer) = 0;
		virtual void bindDescriptorSet(AbstractDescriptorSet* descriptorSet) = 0;
		virtual void draw(int numVertices, int firstVertex) = 0;
	};
	
}

#endif