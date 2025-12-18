#include "AudioComponent.hpp"
#include "AudioController.hpp"

namespace kyra {

	void AudioComponent::setAudioController(AudioController* controller) {
		m_AudioController = controller;
	}

	void AudioComponent::setBuffer(AudioBuffer* buffer) {
		m_AudioBuffer = buffer;
	}

	std::size_t AudioComponent::getHash() const {
		return typeid(AudioComponent).hash_code();
	}

	void AudioComponent::play() {
		if (m_AudioController && m_AudioBuffer) {
			m_AudioController->play(m_AudioBuffer);
		}
	}


}