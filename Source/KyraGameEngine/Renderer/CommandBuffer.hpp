#ifndef KYRAGAMEENGINE_RENDERER_COMMANDBUFFER_HPP
#define KYRAGAMEENGINE_RENDERER_COMMANDBUFFER_HPP

namespace kyra {

	class CommandBuffer {

	public:
		virtual ~CommandBuffer() = default;

		virtual void clear(float r, float g, float b, float a) = 0;

	};

}

#endif