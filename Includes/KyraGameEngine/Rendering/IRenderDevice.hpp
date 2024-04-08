#ifndef KYRAGAMEENGINE_RENDERING_OPENGL_IRENDERDEVICE_HPP
#define KYRAGAMEENGINE_RENDERING_OPENGL_IRENDERDEVICE_HPP


#include "IMesh.hpp"
#include "VertexArray.hpp"
#include "VertexDeclaration.hpp"

namespace kyra {

	class IRenderDevice {
		
		public:
		virtual ~IRenderDevice() = default;
		
		[[nodiscard]] virtual bool create(const IWindow& window) = 0;
		
		virtual void beginDraw() = 0;
		virtual void endDraw() = 0;
		
		[[nodiscard]] virtual bool createMesh(IMesh::Ptr& mesh, const IVertexArray& vertices, const VertexDeclaration& declaration) = 0;
		
	};
	
}

#endif