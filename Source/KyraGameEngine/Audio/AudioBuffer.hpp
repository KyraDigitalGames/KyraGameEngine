#ifndef KYRAGAMEENGINE_AUDIO_AUDIOBUFFER_HPP
#define KYRAGAMEENGINE_AUDIO_AUDIOBUFFER_HPP

#include <string>

namespace kyra {

	class AudioBuffer {

	public:
		virtual ~AudioBuffer() = default;

		virtual bool load(const std::string& file) = 0;

	};

}

#endif