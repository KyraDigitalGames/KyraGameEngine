#include <KyraGameEngine/Framework.hpp>
#include <KyraGameEngine/Log.hpp>
#include <KyraGameEngine/GLEX.hpp>

#include <KyraGameEngine/Rendering/VertexArray.hpp>
#include <KyraGameEngine/Rendering/VertexDeclaration.hpp>
#include <KyraGameEngine/Math/Vector2.hpp>

struct Vertex {
	kyra::Vector2<float> position;
};

class TriangleExample : public kyra::Application {
	
	//kyra::ShaderProgram::Ptr m_ShaderProgram;
	kyra::IMesh::Ptr m_Mesh;
		
	public:
		
	[[nodiscard]] virtual bool onSetup(kyra::ApplicationSettings& settings) final {
		settings.windowSettings.title = "01_TriangleExample";
		settings.windowSettings.style = kyra::WindowStyle::Window;
		return true;
	}
	
	// TODO Add renderer as parameter
	[[nodiscard]] virtual bool onInit(kyra::IWindow& window, kyra::IRenderDevice& renderer) final {
		
		kyra::VertexArray<Vertex> vertices(3);
		vertices[0].position = {0,0};
		vertices[1].position = {0,1};
		vertices[2].position = {1,1};
		
		kyra::VertexDeclaration declaration = {
			{"POS", 0, 2, 2*sizeof(float), 0}
		};
		
		if(!renderer.createMesh(m_Mesh, vertices, declaration)) {
			return false;
		}
		
		
		/*
				
	    if(!renderer.createShaderProgram(m_ShaderProgam, "SimpleShader")) {
			return false;
		}
		
		if(!renderer.createMesh(mesh, vertices, vertexLayout, UsageType::STATIC) {
			return false;
		}
		*/
		
		return true;
	}
	
	virtual void onUpdate() final {
		// DO NOTHING
	}
	
	virtual void onDraw() final {
		// m_ShaderProgram->bind();
		m_Mesh->bind();
		m_Mesh->draw();
	}

};

int main(int argc, char** argv) {
	return TriangleExample().run();
}