#ifndef KYRAGAMEENGINE_RENDERER_COMMANDBUFFERVULKAN_HPP
#define KYRAGAMEENGINE_RENDERER_COMMANDBUFFERVULKAN_HPP

#include <KyraGameEngine/Renderer/CommandBuffer.hpp>

namespace kyra {

	class CommandBufferVulkan : public CommandBuffer {

	public:

		void clear(float r, float g, float b, float a) final;

	};

}

#endif