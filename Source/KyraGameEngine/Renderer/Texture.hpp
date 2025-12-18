#ifndef KYRAGAMEENGINE_RENDERER_TEXTURE_HPP
#define KYRAGAMEENGINE_RENDERER_TEXTURE_HPP

#include <KyraGameEngine/Image/Image.hpp>

namespace kyra {
	class Texture {

	public:
		virtual ~Texture() = default;

		virtual void upload(const Image* image) = 0;
		virtual void bind() = 0;

	};
}

#endif