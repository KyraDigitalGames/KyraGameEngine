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

namespace kyra {

	class AudioDeviceImplementationXAudio2 : public AudioDeviceImplementation {

		IXAudio2* m_Handle;
		IXAudio2MasteringVoice* m_MasterVoice;
		IXAudio2SourceVoice* m_SourceVoice;

		std::map<std::string, std::unique_ptr<AudioBuffer>> m_AudioBuffers;


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
			wfex.nChannels = 1;
			wfex.nSamplesPerSec = 11025L;
			wfex.nAvgBytesPerSec = 11025L;
			wfex.nBlockAlign = 1;
			wfex.wBitsPerSample = 8;
			wfex.cbSize = sizeof(wfex);

			result = m_Handle->CreateSourceVoice(&m_SourceVoice, &wfex);
			if (FAILED(result)) {
				return false;
			}
			return true;
		}

		AudioBuffer* getAudioBuffer(const std::string& file) final {
			auto it = m_AudioBuffers.find(file);
			if (it == m_AudioBuffers.end()) {
				m_AudioBuffers[file] = std::make_unique<AudioBufferXAudio2>();
				if (!m_AudioBuffers[file]->load(file)) {
					return nullptr;
				}
				return m_AudioBuffers[file].get();
			}
			return it->second.get();
		}

		
		void play(AudioBuffer* audioBuffer) final {
			m_SourceVoice->SubmitSourceBuffer(static_cast<AudioBufferXAudio2*>(audioBuffer)->getHandle());
			m_SourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
		}

	};

}

#endif