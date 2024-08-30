#ifndef KYRAGAMEENGINE_RHI_ABSTRACTDESCRIPTORSET_HPP
#define KYRAGAMEENGINE_RHI_ABSTRACTDESCRIPTORSET_HPP

#include "AbstractTexture.hpp"
#include "AbstractShaderProgram.hpp"
#include <unordered_map>

namespace kyra {
	
	class AbstractDescriptorSet {
		
		std::unordered_map<std::string_view, uint32_t> m_UniformLocations;
		
		public:
		virtual ~AbstractDescriptorSet() = default;
		
		virtual void bind(AbstractShaderProgram* shader) = 0;
		
	};
	
}

#endif