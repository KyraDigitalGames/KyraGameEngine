#ifndef KYRAGAMEENGINE_AUDIO_XAUDIO2_AUDIODEVICEIMPLEMENTATIONXAUDIO2_HPP
#define KYRAGAMEENGINE_AUDIO_XAUDIO2_AUDIODEVICEIMPLEMENTATIONXAUDIO2_HPP

#include <KyraGameEngine/Audio/AudioDeviceImplementation.hpp>
#include "AudioBufferXAudio2.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <xaudio2.h>

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

namespace kyra {

	class AudioDeviceImplementationXAudio2 : public AudioDeviceImplementation {

		IXAudio2* m_Handle;
		IXAudio2MasteringVoice* m_MasterVoice;
		IXAudio2SourceVoice* m_SourceVoice;

	public:
		~AudioDeviceImplementationXAudio2() {
			m_Handle->Release();
		}

		bool init() final {
			HRESULT result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
			if (FAILED(result)) {
				return false;
			}
			result = XAudio2Create(&m_Handle, 0, XAUDIO2_DEFAULT_PROCESSOR);
			if (FAILED(result)) {
				return false;
			}

			result = m_Handle->CreateMasteringVoice(
				&m_MasterVoice,
				XAUDIO2_DEFAULT_CHANNELS,
				XAUDIO2_DEFAULT_SAMPLERATE,
				0,
				NULL,
				NULL,
				AudioCategory_GameEffects);
			if (FAILED(result)) {
				return false;
			}

			WAVEFORMATEX wfex = { 0 };
			wfex.wFormatTag = WAVE_FORMAT_PCM;
			wfex.nChannels = 2;
			wfex.nSamplesPerSec = 44100;
			wfex.wBitsPerSample = 16;
			wfex.nBlockAlign = (wfex.nChannels * wfex.wBitsPerSample) / 8;
			wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;
			wfex.cbSize =0;

			result = m_Handle->CreateSourceVoice(&m_SourceVoice, &wfex);
			if (FAILED(result)) {
				return false;
			}
			return true;
		}

		std::shared_ptr<AudioBuffer> getAudioBuffer(const std::vector<unsigned char>& data) final {
			std::shared_ptr<AudioBufferXAudio2> audioBuffer = std::make_shared<AudioBufferXAudio2>();
			if(!audioBuffer->load(data)) {
				return nullptr;
			}
			return std::move(audioBuffer);
		}

		
		void play(std::shared_ptr<AudioBuffer>& buffer) final {
			m_SourceVoice->SubmitSourceBuffer(static_cast<AudioBufferXAudio2*>(buffer.get())->getHandle());
			m_SourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
		}

	};

}

#endif