#ifndef KYRAGAMEENGINE_RENDERER_RHI_RHIDEVICE_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_RHIDEVICE_HPP

#include <KyraGameEngine/Window/Window.hpp>
#include "RHISwapChain.hpp"
#include "RHICommandQueue.hpp"

namespace kyra {

	class RHIDevice {

	public:
		virtual ~RHIDevice() = default;

		struct Descriptor {
			Window::Ptr* window;
		};

		using Ptr = std::unique_ptr<RHIDevice>;
		static RHIDevice::Ptr create();

		virtual bool init(RHIDevice::Descriptor& descriptor) = 0;
		virtual RHISwapChain::Ptr createSwapChain(RHISwapChain::Descriptor& descriptor) = 0;
		virtual RHIShader::Ptr createShader(RHIShader::Descriptor& descriptor) = 0;
		virtual RHIBuffer::Ptr createBuffer(RHIBuffer::Descriptor& descriptor) = 0;
		virtual RHIPipelineLayout::Ptr createPipelineLayout(RHIPipelineLayout::Descriptor& descriptor) = 0;
		virtual RHIRenderPass::Ptr createRenderPass(RHIRenderPass::Descriptor& descriptor) = 0;
		virtual RHIPipelineState::Ptr createPipelineState(RHIPipelineState::Descriptor& descriptor) = 0;
		virtual RHICommandQueue::Ptr createCommandQueue() = 0;
		virtual RHICommandBuffer::Ptr createCommandBuffer() = 0;
	};

}

#endif