#ifndef KYRAGAMEENGINE_AUDIO_AUDIOBUFFER_HPP
#define KYRAGAMEENGINE_AUDIO_AUDIOBUFFER_HPP

#include <string>
#include <vector>

namespace kyra {

	class AudioBuffer {

	public:
		virtual ~AudioBuffer() = default;

		virtual bool load(const std::vector<unsigned char>& data) = 0;

	};

}

#endif