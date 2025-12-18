#include "AudioDeviceImplementationXAudio2.hpp"

namespace kyra {

	std::unique_ptr<AudioDeviceImplementation> AudioDeviceImplementation::create() {
		return std::make_unique<AudioDeviceImplementationXAudio2>();
	}


}