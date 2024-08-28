#ifndef KYRAGAMEENGINE_RHI_ABSTRACTFRAMEBUFFER_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTFRAMEBUFFER_HPP

#include "AbstractRenderTarget.hpp"

namespace kyra {
	
	class AbstractFramebuffer : public AbstractRenderTarget {
		
		public:
		virtual ~AbstractFramebuffer() = default;
		
	};
}

#endif