#ifndef KYRAGAMEENGINE_RHI_ABSTRACTVERTEXBUFFER_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTVERTEXBUFFER_HPP

#include <cstdint>

namespace kyra {
	
	class AbstractVertexBuffer {
		
		public:
		virtual ~AbstractVertexBuffer() = default;
		
		virtual void resize(uint32_t size) = 0;
		virtual void setData(uint32_t size, const void* data) = 0;
		virtual void setSubData(uint32_t size, const void* data, uint32_t offset) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		[[nodiscard]] virtual uint32_t getSize() const = 0;
	};
	
}

#endif