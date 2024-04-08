#ifndef KYRAGAMEENGINE_RENDERING_VERTEXDECLARATION_HPP
#define KYRAGAMEENGINE_RENDERING_VERTEXDECLARATION_HPP

#include <vector>

namespace kyra {
	
	struct VertexDeclarationEntry {
		std::string id; // Used by DX
		std::size_t index; // Used by OpenGL
		std::size_t type;
		std::size_t size;
		std::size_t stride;
		
		VertexDeclarationEntry(std::string id, std::size_t index, std::size_t type, std::size_t size, std::size_t stride) {
			
		}
		
	};
	
	using VertexDeclaration = std::vector<VertexDeclarationEntry>;
	
	
}

#endif