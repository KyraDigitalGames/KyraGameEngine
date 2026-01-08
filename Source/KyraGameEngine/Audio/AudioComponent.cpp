#include "AudioComponent.hpp"
#include "AudioController.hpp"

namespace kyra {

	void AudioComponent::setAudioController(AudioController* controller) {
		m_AudioController = controller;
	}

	void AudioComponent::setBuffer(AudioAsset::Handle& handle) {
		m_AudioHandle = handle;
	}

	std::size_t AudioComponent::getHash() const {
		return typeid(AudioComponent).hash_code();
	}

	void AudioComponent::play() {
		if (m_AudioController) {
			m_AudioController->play(m_AudioHandle);
		}
	}


}