#ifndef KYRAGAMEENGINE_AUDIO_AUDIOCONTROLLER_HPP
#define KYRAGAMEENGINE_AUDIO_AUDIOCONTROLLER_HPP

#include "AudioBuffer.hpp"
#include "AudioComponent.hpp"
#include "AudioDeviceImplementation.hpp"

#include <KyraGameEngine/Core/System.hpp>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace kyra {

	class AudioController : public System {

		std::unique_ptr<AudioDeviceImplementation> m_Implementation;
		std::vector<std::shared_ptr<AudioComponent>> m_AudioComponents;

	public:
		

		bool init() {
			m_Implementation = AudioDeviceImplementation::create();
			return m_Implementation->init();
		}

		AudioBuffer* getAudioBuffer(const std::string& file) {
			if (m_Implementation) {
				return m_Implementation->getAudioBuffer(file);
			}
			return nullptr;
		}

		AudioComponent* createAudioComponent() {
			m_AudioComponents.emplace_back(std::make_shared<AudioComponent>());
			AudioComponent* temp = m_AudioComponents.back().get();
			temp->setAudioController(this);
			return temp;
		}


		void play(AudioBuffer* audioBuffer) {
			if (m_Implementation) {
				m_Implementation->play(audioBuffer);
			}
		}

		void update(float deltaTime) final {

		}


	};

}

#endif