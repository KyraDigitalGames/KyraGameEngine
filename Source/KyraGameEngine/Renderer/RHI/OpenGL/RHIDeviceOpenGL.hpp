#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIDEVICEOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHIDEVICEOPENGL_HPP

#include <KyraGameEngine/Renderer/RHI/RHIDevice.hpp>

#include "OpenGL.hpp"
#include "OpenGLContext.hpp"
#include "RHISwapChainOpenGL.hpp"
#include "RHIBufferOpenGL.hpp"
#include "RHIShaderOpenGL.hpp"
#include "RHIPipelineLayoutOpenGL.hpp"
#include "RHIRenderPassOpenGL.hpp"
#include "RHIPipelineStateOpenGL.hpp"
#include "RHICommandBufferOpenGL.hpp"
#include "RHICommandQueueOpenGL.hpp"

namespace kyra {

	class RHIDeviceOpenGL : public RHIDevice {

		OpenGLContext::Ptr m_OpenGLContext;

	public:

		bool init(RHIDevice::Descriptor& descriptor) final {
			m_OpenGLContext = OpenGLContext::create();
			if (!m_OpenGLContext->init(*descriptor.window)) {
				return false;
			}
			return true;
		}

		virtual RHISwapChain::Ptr createSwapChain(RHISwapChain::Descriptor& descriptor) final {
			RHISwapChain::Ptr swapChain = std::make_unique<RHISwapChainOpenGL>(m_OpenGLContext);
			if (!swapChain->init(descriptor)) {
				return nullptr;
			}
			return std::move(swapChain);
		}

		virtual RHIShader::Ptr createShader(RHIShader::Descriptor& descriptor) {
			RHIShader::Ptr shader = std::make_unique<RHIShaderOpenGL>();
			if (!shader->init(descriptor)) {
				return nullptr;
			}
			return std::move(shader);
		}

		virtual RHIBuffer::Ptr createBuffer(RHIBuffer::Descriptor& descriptor) {
			RHIBuffer::Ptr buffer = std::make_unique<RHIBufferOpenGL>();
			if (!buffer->init(descriptor)) {
				return nullptr;
			}
			return std::move(buffer);
		}

		virtual RHIPipelineLayout::Ptr createPipelineLayout(RHIPipelineLayout::Descriptor& descriptor) {
			RHIPipelineLayout::Ptr pipelineLayout = std::make_unique<RHIPipelineLayoutOpenGL>();
			if (!pipelineLayout->init(descriptor)) {
				return nullptr;
			}
			return std::move(pipelineLayout);
		}

		virtual RHIRenderPass::Ptr createRenderPass(RHIRenderPass::Descriptor& descriptor) {
			RHIRenderPass::Ptr renderPass = std::make_unique<RHIRenderPassOpenGL>();
			if (!renderPass->init(descriptor)) {
				return nullptr;
			}
			return std::move(renderPass);
		}

		virtual RHIPipelineState::Ptr createPipelineState(RHIPipelineState::Descriptor& descriptor) final {
			RHIPipelineState::Ptr pipelineState = std::make_unique<RHIPipelineStateOpenGL>();
			if (!pipelineState->init(descriptor)) {
				return nullptr;
			}
			return std::move(pipelineState);
		}

		virtual RHICommandQueue::Ptr createCommandQueue() final {
			return std::make_unique<RHICommandQueueOpenGL>();
		}

		virtual RHICommandBuffer::Ptr createCommandBuffer() final {
			return std::make_unique<RHICommandBufferOpenGL>();
		}

	};

}

#endif