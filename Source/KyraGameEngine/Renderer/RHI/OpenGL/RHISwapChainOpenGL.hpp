#ifndef KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHISWAPCHAINOPENGL_HPP
#define KYRAGAMEENGINE_RENDERER_RHI_OPENGL_RHISWAPCHAINOPENGL_HPP

#include "RHIFrameBufferOpenGL.hpp"
#include "OPenGLContext.hpp"
#include <KyraGameEngine/Renderer/RHI/RHISwapChain.hpp>

namespace kyra {

	class RHISwapChainOpenGL : public RHISwapChain {

		RHIFrameBufferOpenGL m_FrameBuffer;
		OpenGLContext::Ptr& m_OpenGLContext;

	public:
		RHISwapChainOpenGL(OpenGLContext::Ptr& context) : m_OpenGLContext(context) {

		}

		bool init(const RHISwapChain::Descriptor& descriptor) final {

			return true;
		}

		uint32_t acquireNextImage() final {
			return 0;
		}

		virtual RHIFrameBuffer* getFrameBuffer(uint32_t index) final {
			return &m_FrameBuffer;
		}

		virtual void present(uint32_t index) final {
			m_OpenGLContext->swapBuffers();
		}
	};

}

#endif