#ifndef KYRAGAMEENGINE_RHI_OPENGL_COMMANDBUFFEROPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_COMMANDBUFFEROPENGL_HPP

#include <KyraGameEngine/Platform/OpenGL/GLEX.hpp>
#include <KyraGameEngine/RHI/AbstractCommandBuffer.hpp>

namespace kyra {
	
	class CommandBufferOpenGL : public AbstractCommandBuffer {
		
		AbstractPipeline* m_BoundPipeline = nullptr;
		AbstractVertexBuffer* m_BoundVertexBuffer = nullptr;
		
		AbstractPipeline* m_Pipeline = nullptr;
		AbstractVertexBuffer* m_VertexBuffer = nullptr;
		
		public:
		
		void bindPipeline(AbstractPipeline* pipeline) final;

		void clear() final;
		
		void bindVertexBuffer(AbstractVertexBuffer* vertexBuffer) final;
		
		void draw(int firstVertex, int numVertices) final;
		
	};
	
}

#endif