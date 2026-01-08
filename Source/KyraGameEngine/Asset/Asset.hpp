#ifndef KYRAGAMEENGINE_ASSET_ASSET_HPP
#define KYRAGAMEENGINE_ASSET_ASSET_HPP

#include <vector>
#include <KyraGameEngine/Image/Image.hpp>
#include <Windows.h>
#include <XAudio2.h>
#include <iostream>

namespace kyra {

	enum class AssetType {
		Invalid,
		Texture,
		Audio
	};

	using AssetId = std::uint32_t;
	static constexpr AssetId INVALID_ASSET_ID = 0;

	class AssetOwner {
		public:
		virtual ~AssetOwner() = default;

		virtual void release(AssetType type, AssetId id) = 0;
	};

	struct Asset {
		
		AssetId id = INVALID_ASSET_ID;
		std::uint32_t index = 0;
		std::uint32_t refCount = 0;
		std::uint32_t generation = 0;
		bool isLoaded = false;
		AssetOwner* owner = nullptr;

		struct Handle {
	
			Asset* asset = nullptr;
			AssetType type = AssetType::Invalid;

			Handle() : asset(nullptr) {
			
			}

			Handle(const Handle& handle)  {
				type = handle.type;
				asset = handle.asset;
				if (asset) {
					asset->refCount++;
				}
			}

			Handle(AssetType _type, Asset* asset, AssetOwner* owner) : type(_type), asset(asset) {
				if (asset) {
					asset->owner = owner;
					asset->refCount++;
				}
			}

			~Handle() {
				if (asset) {
					asset->refCount--;
					if (asset->refCount < 1 && asset->owner) {
						asset->owner->release(type, asset->id);
					}
				}
			}

			Handle& operator=(const Handle& handle) {
				asset = handle.asset;
				if (asset) {
					asset->refCount++;
				}
				return *this;
			}

			constexpr bool isValid() const {
				return asset != nullptr;
			}


		};

	};
		
	struct TextureAsset : public Asset {
		Image image;
	};

	struct AudioAsset : public Asset {
		std::vector<unsigned char> data;
	};

	class AudioLoader {

	public:

		bool load(const std::string& file, std::vector<unsigned char>& outData) {
			WAVEFORMATEXTENSIBLE format;

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
			ReadFile(audioFile, &format, chunkDataSize, &bytesRead, NULL);

			ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL);

			std::vector<unsigned char> extraBytes;
			extraBytes.resize(2048);

			while (chunkType != 'atad') {
				ReadFile(audioFile, &chunkDataSize, sizeof(DWORD), &bytesRead, NULL);
				ReadFile(audioFile, &extraBytes[0], chunkDataSize, &bytesRead, NULL);
				if (!ReadFile(audioFile, &chunkType, sizeof(DWORD), &bytesRead, NULL)) {
					CloseHandle(audioFile);
					return false;
				}
			}

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

			outData.resize(chunkDataSize);
			memcpy(outData.data(), audioData, chunkDataSize);
			free(audioData);

			CloseHandle(audioFile);
			return true; 
		}

	};



}


#endif