#ifndef KYRAGAMEENGINE_GRAPHICS_VERTEX2D_HPP
#define KYRAGAMEENGINE_GRAPHICS_VERTEX2D_HPP

#include <KyraGameEngine/Math/Vector2.hpp>
#include <KyraGameEngine/Math/Vector4.hpp>

namespace kyra {

	struct Vertex2D {
		Vector2<float> position;
		Vector2<float> uv;
		Vector4<float> color;
	};

}

#endif