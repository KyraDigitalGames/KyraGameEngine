#ifndef KYRAGAMEENGINE_RENDERING_OPENGL_MESHGL_HPP
#define KYRAGAMEENGINE_RENDERING_OPENGL_MESHGL_HPP

#include <KyraGameEngine/Rendering/IMesh.hpp> 

namespace kyra {
	
	class MeshGL : public IMesh {
		
		public:
				
		virtual bool create(const IVertexArray& vertices, const VertexDeclaration& declaration) {
			return true;
		}
		
		virtual void bind() final {
			
		}

		virtual void draw() final {
			
		}

	};
	
}

#endif