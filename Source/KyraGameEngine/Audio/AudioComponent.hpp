#ifndef KYRAGAMEENGINE_AUDIO_AUDIOCOMPONENT_HPP
#define KYRAGAMEENGINE_AUDIO_AUDIOCOMPONENT_HPP

#include "AudioBuffer.hpp"
#include <KyraGameEngine/Scene/Component.hpp>
#include <typeinfo>

namespace kyra {

	class AudioController;
	class AudioComponent : public Component {

		AudioBuffer* m_AudioBuffer = nullptr;
		AudioController* m_AudioController = nullptr;
	public:

		void setAudioController(AudioController* controller);

		void setBuffer(AudioBuffer* buffer);

		void play();

		std::size_t getHash() const final;

	};

}


#endif