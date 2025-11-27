#ifndef KYRAGAMEENGINE_RENDERER_RENDERER_HPP
#define KYRAGAMEENGINE_RENDERER_RENDERER_HPP

#include "RenderDeviceImplementation.hpp"
#include <KyraGameEngine/Window/Window.hpp>
#include <memory>

namespace kyra {

	enum class RenderDeviceType {
		OpenGL,
		Vulkan,
		Metal,
		DirectX11,
		DirectX12
	};

	struct RendererDescriptor {
		RenderDeviceType type = RenderDeviceType::OpenGL;
		Window* window = nullptr;
	};

	class Renderer {

		std::unique_ptr<RenderDeviceImplementation> m_Implementation;

	public:
		
		bool init(const RendererDescriptor& descriptor);
		Swapchain* acquireSwapchain();
		CommandBuffer* acquireCommandBuffer();

	};

}

#endif