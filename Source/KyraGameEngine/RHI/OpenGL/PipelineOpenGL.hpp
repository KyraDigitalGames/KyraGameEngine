#ifndef KYRAGAMEENGINE_RHI_OPENGL_PIPELINEOPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_PIPELINEOPENGL_HPP

#include "GLEX.hpp"
#include <KyraGameEngine/RHI/AbstractPipeline.hpp>


namespace kyra {
	
	class PipelineOpenGL : public AbstractPipeline {
		
		GLuint m_Id = 0;
		AbstractShaderProgram* m_ShaderProgram = nullptr;
		BufferLayout m_Layout;
		
		public:
		PipelineOpenGL() {
			glGenVertexArrays(1, &m_Id);
		}
		
		~PipelineOpenGL() {
			glDeleteVertexArrays(1,&m_Id);
		}
		
		
		[[nodiscard]] bool init(const PipelineDescriptor& pipeline) final;
		void bind() final;
	};
}

#endif