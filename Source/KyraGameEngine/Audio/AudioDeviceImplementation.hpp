#ifndef KYRAGAMEENGINE_AUDIO_AUDIODEVICEIMPLEMENTATION_HPP
#define KYRAGAMEENGINE_AUDIO_AUDIODEVICEIMPLEMENTATION_HPP

#include "AudioComponent.hpp"
#include "AudioBuffer.hpp"

#include <memory>
#include <string>

namespace kyra {

	class AudioDeviceImplementation {

	public:
		virtual ~AudioDeviceImplementation() = default;

		static std::unique_ptr<AudioDeviceImplementation> create();

		virtual bool init() = 0;
		virtual AudioBuffer* getAudioBuffer(const std::string& file) = 0;
		virtual void play(AudioBuffer* audioBuffer) = 0;

	};

}

#endif