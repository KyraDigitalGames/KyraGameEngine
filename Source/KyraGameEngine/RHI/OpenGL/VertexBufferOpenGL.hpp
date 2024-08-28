#ifndef KYRAGAMEENGINE_RHI_OPENGL_VERTEXBUFFEROPENGL_HPP
#define KYRAGAMEENGINE_RHI_OPENGL_VERTEXBUFFEROPENGL_HPP

#include "GLEX.hpp"
#include <KyraGameEngine/RHI/AbstractVertexBuffer.hpp>

namespace kyra {
	
	class VertexBufferOpenGL : public AbstractVertexBuffer {
		
		uint32_t m_Handle = 0;
		uint32_t m_Size   = 0;
		
		public:
		VertexBufferOpenGL();
		virtual ~VertexBufferOpenGL();
		
		void resize(uint32_t size) final;
		
		void setData(uint32_t size, const void* data) final;
		
		void setSubData(uint32_t size, const void* data, uint32_t offset) final;
		
		void bind() final;
		
		void unbind() final;
		
		[[nodiscard]] uint32_t getSize() const final;
	};
	
}

#endif