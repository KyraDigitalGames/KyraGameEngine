#ifndef KYRAGAMEENGINE_AUDIO_XAUDIO2_AUDIOBUFFERXAUDIO2_HPP
#define KYRAGAMEENGINE_AUDIO_XAUDIO2_AUDIOBUFFERXAUDIO2_HPP


#include <KyraGameEngine/Audio/AudioBuffer.hpp>
#include <xaudio2.h>
#include <string>

namespace kyra {

	class AudioBufferXAudio2 : public AudioBuffer {

		XAUDIO2_BUFFER m_Buffer;

	public:

		bool load(const std::vector<unsigned char>& data) {
			m_Buffer.pAudioData = &data[0];
			m_Buffer.AudioBytes = data.size();
			m_Buffer.Flags = XAUDIO2_END_OF_STREAM;
			m_Buffer.LoopCount = 0;
			m_Buffer.LoopLength = 0;
			m_Buffer.LoopBegin = 0;
			return true;
		}

		const XAUDIO2_BUFFER* getHandle() const {
			return &m_Buffer;
		}


	};

}

#endif