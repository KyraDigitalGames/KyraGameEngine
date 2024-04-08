#ifndef KYRAGAMEENGINE_RENDERING_IMESH_HPP
#define KYRAGAMEENGINE_RENDERING_IMESH_HPP

#include <memory>

#include "VertexArray.hpp"
#include "VertexDeclaration.hpp"

namespace kyra {
	
	class IMesh {
		
		public:
		
		using Ptr = std::shared_ptr<IMesh>;
		
		virtual bool create(const IVertexArray& vertices, const VertexDeclaration& declaration) = 0;
		virtual void bind() = 0;
		virtual void draw() = 0;
		
	};
	
}

#endif