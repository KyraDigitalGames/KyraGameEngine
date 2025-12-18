#ifndef KYRAGAMEENGINE_AUDIO_XAUDIO2_AUDIOBUFFERXAUDIO2_HPP
#define KYRAGAMEENGINE_AUDIO_XAUDIO2_AUDIOBUFFERXAUDIO2_HPP


#include <KyraGameEngine/Audio/AudioBuffer.hpp>
#include <xaudio2.h>
#include <string>

namespace kyra {

	class AudioBufferXAudio2 : public AudioBuffer {

		XAUDIO2_BUFFER m_Buffer;
		WAVEFORMATEXTENSIBLE m_Format;


	public:

		bool load(const std::string& file) {
			HANDLE audioFile = CreateFileA(
				file.c_str(),
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

			if (audioFile == INVALID_HANDLE_VALUE) {
				return false;
			}

			if (SetFilePointer(audioFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
				return false;
			}

			DWORD chunkType = 0;
			DWORD chunkDataSize = 0;
			DWORD fileFormat = 0;
			DWORD bytesRead = 0;

			ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);

			if (chunkType != 'FFIR') {
				CloseHandle(audioFile);
				return false;
			}
			ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL); 
			ReadFile(audioFile, &fileFormat, sizeof(DWORD), &bytesRead, NULL);    

			if (fileFormat != 'EVAW') {
				CloseHandle(audioFile);
				return false;
			}

			ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);

			if (chunkType != ' tmf') {
				CloseHandle(audioFile);
				return false;
			}

			ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL);
			ReadFile(audioFile, &m_Format, chunkDataSize, &bytesRead, NULL); 

			ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);    

			if (chunkType != 'atad') {
				CloseHandle(audioFile);
				return false;
			}

			ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL);

			BYTE* audioData = (BYTE*)malloc(chunkDataSize);

			if (!audioData) {
				CloseHandle(audioFile);
				return false;
			}

			ReadFile(audioFile, audioData, chunkDataSize, &bytesRead, NULL);
			
			m_Buffer.pAudioData = audioData;
			m_Buffer.AudioBytes = chunkDataSize;

			CloseHandle(audioFile);

			return true;
		}

		const XAUDIO2_BUFFER* getHandle() const {
			return &m_Buffer;
		}


	};

}

#endif