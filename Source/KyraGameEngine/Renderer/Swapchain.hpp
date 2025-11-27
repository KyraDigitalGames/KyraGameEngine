#ifndef KYRAGAMEENGINE_RENDERER_SWAPCHAIN_HPP
#define KYRAGAMEENGINE_RENDERER_SWAPCHAIN_HPP

#include <KyraGameEngine/Window/Window.hpp>

namespace kyra {

	struct SwapchainDescriptor {
		Window* window = nullptr;
	};

	class Swapchain {

	public:
		virtual ~Swapchain() = default;

		virtual bool init(SwapchainDescriptor& descriptor) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual void swap() = 0;

	};

}

#endif