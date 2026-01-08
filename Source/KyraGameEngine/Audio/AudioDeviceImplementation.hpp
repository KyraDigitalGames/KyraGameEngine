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
		virtual std::shared_ptr<AudioBuffer> getAudioBuffer(const std::vector<unsigned char>& data) = 0;
		virtual void play(std::shared_ptr<AudioBuffer>& buffer) = 0;

	};

}

#endif