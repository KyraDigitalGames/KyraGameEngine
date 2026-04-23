#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHIBUFFER_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHIBUFFER_HPP

#include <memory>

namespace kyra {

	class RHIBuffer {

	public:
		virtual ~RHIBuffer() = default;

		using Ptr = std::unique_ptr<RHIBuffer>;

		enum class Type {
			Vertex
		};

		struct Descriptor {
			std::size_t size = 0;
			Type usage;
		};

		virtual bool init(const RHIBuffer::Descriptor& descriptor) = 0;
		virtual void upload(void* data, std::size_t size) = 0;

	};
}

#endif