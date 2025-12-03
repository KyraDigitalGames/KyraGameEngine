#ifndef KYRAGAMEENGINE_RENDERER_SWAPCHAINOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_SWAPCHAINOPENGL_HPP

#include <KyraGameEngine/Renderer/Swapchain.hpp>
#include <Windows.h>
#include <gl/GL.h>

namespace kyra {

	class SwapchainOpenGL : public Swapchain {

		HDC m_DeviceContext = NULL;
		HGLRC m_RenderContext = NULL;

	public:
		virtual ~SwapchainOpenGL();

		bool init(SwapchainDescriptor& descriptor) final;
		void setVSync(bool enabled) final;
		void swap() final;

	};

}

#endif