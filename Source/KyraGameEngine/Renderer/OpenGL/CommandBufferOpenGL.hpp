#ifndef KYRAGAMEENGINE_RENDERER_COMMANDBUFFEROPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_COMMANDBUFFEROPENGL_HPP

#include <KyraGameEngine/Renderer/CommandBuffer.hpp>

namespace kyra {

	class CommandBufferOpenGL : public CommandBuffer {

	public:

		void clear(float r, float g, float b, float a) final;

	};

}

#endif