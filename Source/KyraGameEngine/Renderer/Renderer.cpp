#include "Renderer.hpp"

#include <KyraGameEngine/Log/Logger.hpp>

#include <assert.h>

#define KYRA_RENDERER_VULKAN

#ifdef KYRA_RENDERER_VULKAN
#include <KyraGameEngine/Renderer/Vulkan/RenderDeviceImplementationVulkan.hpp>
#endif

#ifdef  KYRA_RENDERER_OPENGL
#include <KyraGameEngine/Renderer/OpenGL/RenderDeviceImplementationOpenGL.hpp>
#endif

#ifdef  KYRA_RENDERER_DIRECTX11

#endif

#ifdef  KYRA_RENDERER_DIRECTX12

#endif

namespace kyra {

	bool Renderer::init(const RendererDescriptor& descriptor) {
#ifdef KYRA_RENDERER_VULKAN
		if (descriptor.type == RenderDeviceType::Vulkan) {
			m_Implementation = std::make_unique<RenderDeviceImplementationVulkan>();
		}
#endif

#ifdef  KYRA_RENDERER_OPENGL
		if (descriptor.type == RenderDeviceType::OpenGL) {
			m_Implementation = std::make_unique<RenderDeviceImplementationOpenGL>();
		}
#endif

#ifdef  KYRA_RENDERER_DIRECTX11

#endif

#ifdef  KYRA_RENDERER_DIRECTX12

#endif
		if (descriptor.window == nullptr) {
			KYRA_LOG_ERROR("RendererDescriptor - Pointer to Window is nullptr");
			return false;
		}
		RenderDeviceDescriptor renderDeviceDescriptor;
		renderDeviceDescriptor.window = descriptor.window;
		return m_Implementation->init(renderDeviceDescriptor);
	}

	Swapchain* Renderer::acquireSwapchain() {
		assert(m_Implementation);
		if (!m_Implementation) {
			return nullptr;
		}
		return m_Implementation->acquireSwapchain();
	}

	CommandBuffer* Renderer::acquireCommandBuffer() {
		assert(m_Implementation);
		if (!m_Implementation) {
			return nullptr;
		}
		return m_Implementation->acquireCommandBuffer();
	}


	void Renderer::setRenderPipeline(RenderPipeline renderPipeline) {
		m_RenderPipeline = renderPipeline;
	}

	void Renderer::update() {
		m_RenderPipeline.renderFrame();
	}

}