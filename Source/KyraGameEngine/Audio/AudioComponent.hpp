#ifndef KYRAGAMEENGINE_AUDIO_AUDIOCOMPONENT_HPP
#define KYRAGAMEENGINE_AUDIO_AUDIOCOMPONENT_HPP

#include "AudioBuffer.hpp"
#include <KyraGameEngine/Scene/Component.hpp>
#include <KyraGameEngine/Asset/Asset.hpp>
#include <typeinfo>

namespace kyra {

	class AudioController;
	class AudioComponent : public Component {

		AudioAsset::Handle m_AudioHandle;
		AudioController* m_AudioController = nullptr;
	
	public:

		void setAudioController(AudioController* controller);

		void setBuffer(AudioAsset::Handle& handle);

		void play();

		bool isPlaying() const {

		}

		std::size_t getHash() const final;

	};

}


#endif