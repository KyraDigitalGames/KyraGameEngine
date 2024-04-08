#ifndef KYRAGAMEENGINE_RENDERING_OPENGL_RENDERDEVICEGL_HPP
#define KYRAGAMEENGINE_RENDERING_OPENGL_RENDERDEVICEGL_HPP

#include <KyraGameEngine/Rendering/OpenGL/GLContextWGL.hpp>
#include <KyraGameEngine/Rendering/IRenderDevice.hpp>

#include "MeshGL.hpp"

namespace kyra {
	
	class RenderDeviceGL : public IRenderDevice {

		GLContext m_Context;
		
		public:
		
		virtual bool create(const IWindow& window) final {
			if(!m_Context.create(window)) {
				return false;
			}
			return true;
		}
		
		virtual void beginDraw() final {
			glClear(GL_COLOR_BUFFER_BIT);
		}
		
		virtual void endDraw() final {
			m_Context.swapBuffers();
		}
		
		[[nodiscard]] virtual bool createMesh(IMesh::Ptr& mesh, const IVertexArray& vertices, const VertexDeclaration& declaration) final {
			mesh = std::make_shared<MeshGL>();
			return mesh->create(vertices, declaration);
		}
		
	};
	
	using RenderDevice = RenderDeviceGL;
	
}

#endif