#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHISHADER_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHISHADER_HPP

#include <memory>

namespace kyra {

	class RHIShader {

	public:
		virtual ~RHIShader() = default;

		enum class Type {
			Vertex,
			Fragment
		};

		struct Descriptor {
			Type type;
			const char* data;
			std::size_t size;
		};

		using Ptr = std::unique_ptr<RHIShader>;

		virtual bool init(const RHIShader::Descriptor& descriptor) = 0;

	};

}

#endif