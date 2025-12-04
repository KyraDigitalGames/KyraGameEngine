#ifndef KYRAGAMEENGINE_RENDERING_RENDERPIPELINESTATE_HPP
#define KYRAGAMEENGINE_RENDERING_RENDERPIPELINESTATE_HPP

#include <vector>
#include "VertexBuffer.hpp"

#include <KyraGameEngine/Math/Matrix4.hpp>

namespace kyra {

	enum class ShaderType {
		Vertex,
		Fragment
	};

	enum class ShaderLanguage {
		GLSL
	};

	struct ShaderDescriptor {
		ShaderType type = ShaderType::Vertex;
		ShaderLanguage language = ShaderLanguage::GLSL;
		const char* data = nullptr;
	};

	struct RenderPipelineStateDescriptor {
		std::vector<ShaderDescriptor> shaders;
	};

	class RenderPipelineState {

	public:
		~RenderPipelineState() = default;

		virtual bool init(const RenderPipelineStateDescriptor& descriptor) = 0;
		virtual void uploadUniform(const char* name, const Matrix4& matrix) = 0;
		virtual void bind() = 0;
	};

}

#endif