#ifndef KYRAGAMEENGINE_RENDERER_VERTEXBUFFER_HPP
#define KYRAGAMEENGINE_RENDERER_VERTEXBUFFER_HPP

#include <vector>

namespace kyra {

	struct VertexBufferDescriptor {
		std::size_t size = 0;
		void* data = nullptr;
	};

	class VertexBuffer {

	public:
		virtual ~VertexBuffer() = default;

		virtual bool init(const VertexBufferDescriptor& descriptor) = 0;
		virtual void bind() = 0;
	};

}

#endif