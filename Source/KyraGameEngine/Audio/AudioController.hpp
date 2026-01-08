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
#include <KyraGameEngine/Asset/AssetManager.hpp>

namespace kyra {

	struct AudioControllerDescriptor{
		AssetManager * assetManager = nullptr;
	};

	class AudioController : public System {

		AssetManager* m_AssetManager = nullptr;
		std::unique_ptr<AudioDeviceImplementation> m_Implementation;
		std::vector<std::shared_ptr<AudioComponent>> m_AudioComponents;

		std::unordered_map<AssetId, std::shared_ptr<AudioBuffer>> m_AudioBuffers;

	public:
		
		bool init(AudioControllerDescriptor& descriptor) {
			if(!descriptor.assetManager) {
				return false;
			}
			m_AssetManager = descriptor.assetManager;
			m_Implementation = AudioDeviceImplementation::create();
			return m_Implementation->init();
		}
		
		AudioComponent* createAudioComponent() {
			m_AudioComponents.emplace_back(std::make_shared<AudioComponent>());
			AudioComponent* temp = m_AudioComponents.back().get();
			temp->setAudioController(this);
			return temp;
		}


		void play(AudioAsset::Handle& handler) {
			if (m_Implementation) {
				if (!handler.asset->isLoaded) {
					return;
				}
				auto it = m_AudioBuffers.find(handler.asset->id);
				if (it != m_AudioBuffers.end()) {
					m_Implementation->play(it->second);
				}
			}
		}

		void update(float deltaTime) final {
			auto& audioLoadingQueue = m_AssetManager->getLoadingQueue<AudioAsset>();
			if(audioLoadingQueue.size() > 0) {
				for(auto it = audioLoadingQueue.begin(); it != audioLoadingQueue.end(); ) {
					AudioAsset* audioAsset = m_AssetManager->getAudioAsset(*it);
					if(audioAsset && audioAsset->isLoaded && audioAsset->index == 0) {
						audioAsset->index = m_AudioBuffers.size();
						m_AudioBuffers[audioAsset->index] = m_Implementation->getAudioBuffer(audioAsset->data);
					} else {
						++it;
					}
				}
			}
		}


	};

}

#endif