#include "SwapChainOpenGL.hpp"

namespace kyra {
	
	bool SwapChainOpenGL::init(const SwapChainDescriptor& swapChainDescriptor ) {
		if(!m_Context.init( *(swapChainDescriptor.window))) {
			return false;
		}
		return true;
	}
		
	void SwapChainOpenGL::present() {
		m_Context.swapBuffers();
	}
}
