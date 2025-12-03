#ifndef KYRAGAMEENGINE_RENDERER_SWAPCHAINVULKAN_HPP
#define KYRAGAMEENGINE_RENDERER_SWAPCHAINVULKAN_HPP

#include <KyraGameEngine/Renderer/Swapchain.hpp>


namespace kyra {

	class SwapchainVulkan : public Swapchain {

	public:
		virtual ~SwapchainVulkan();

		bool init(SwapchainDescriptor& descriptor) final;
		void setVSync(bool enabled) final;
		void swap() final;

	};

}

#endif