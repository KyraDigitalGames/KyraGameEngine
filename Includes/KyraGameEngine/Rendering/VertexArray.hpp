#ifndef KYRAGAMENGINE_RENDERING_VERTEXARRAY_HPP
#define KYRAGAMENGINE_RENDERING_VERTEXARRAY_HPP

#include <vector>

namespace kyra {
	
	class IVertexArray {
		
		public:
		virtual ~IVertexArray() = default;
		
		
	};
	
	template<class VertexType>
	class VertexArray : public IVertexArray {
		
		std::vector<VertexType> m_Vertices;
		
		public:
		VertexArray(std::size_t size = 0) {
			if(size) {
				m_Vertices.resize(size);
			}
		}
		
		VertexType& operator[] (std::size_t index) {
			return m_Vertices[index];
		}
		
	};
	
}

#endif