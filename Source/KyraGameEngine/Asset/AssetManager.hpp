#ifndef KYRAGAMEENGINE_ASSET_ASSETMANAGER_HPP
#define KYRAGAMEENGINE_ASSET_ASSETMANAGER_HPP

#include "Asset.hpp"
#include <KyraGameEngine/Core/System.hpp>
#include <KyraGameEngine/Renderer/Renderer.hpp>
#include <string>
#include <unordered_map>

namespace kyra {


	class AssetManager : public System, public AssetOwner {

		AssetId m_NextTextureId = 1;
		std::unordered_map<AssetId, TextureAsset> m_TextureAssets;
		std::vector<AssetId> m_TextureLoadingQueue;

		AssetId m_NextAudioId = 1;
		std::unordered_map<AssetId, AudioAsset> m_AudioAssets;
		std::vector<AssetId> m_AudioLoadingQueue;


		void releaseAudio(AssetId id) {
			auto it = m_AudioAssets.find(id);
			if (it != m_AudioAssets.end()) {
				if (it->second.refCount < 1) {
					m_AudioAssets.erase(it);
				}
			}
		}

		void releaseTexture(AssetId id) {
			auto it = m_TextureAssets.find(id);
			if (it != m_TextureAssets.end()) {
				if (it->second.refCount < 1) {
					m_TextureAssets.erase(it);
				}
			}
		}


	public:

		template<class AssetType> 
		bool isLoadingQueueEmpty() const;

		template<class AssetType>
		std::vector<AssetId>& getLoadingQueue();

		TextureAsset::Handle loadTexture(const std::string& filepath) {
			TextureAsset textureAsset;
			if (!textureAsset.image.load(filepath)) {
				return TextureAsset::Handle();
			}
			textureAsset.id = m_NextTextureId++;
			textureAsset.isLoaded = true;
			m_TextureAssets[textureAsset.id] = textureAsset;
			m_TextureLoadingQueue.push_back(textureAsset.id);
			return std::move(TextureAsset::Handle(AssetType::Texture, &m_TextureAssets[textureAsset.id], this));
		}

		TextureAsset* getTextureAsset(AssetId id) {
			auto it = m_TextureAssets.find(id);
			if (it != m_TextureAssets.end()) {
				return &it->second;
			}
			return nullptr;
		}
		
		
		AudioAsset::Handle loadAudio(const std::string& filepath) {
			AudioAsset audioAsset;
			AudioLoader audioLoader;
			if(!audioLoader.load(filepath, audioAsset.data)) {
				return AudioAsset::Handle();
			}
			audioAsset.id = m_NextAudioId++;
			audioAsset.isLoaded = true;
			m_AudioAssets[audioAsset.id] = audioAsset;
			m_AudioLoadingQueue.push_back(audioAsset.id);
			return std::move(AudioAsset::Handle(AssetType::Audio, &m_AudioAssets[audioAsset.id], this));
		}

		AudioAsset* getAudioAsset(AssetId id) {
			auto it = m_AudioAssets.find(id);
			if (it != m_AudioAssets.end()) {
				return &it->second;
			}
			return nullptr;
		}

		void release(AssetType type, AssetId id) {
			if(type == AssetType::Texture) {
				releaseTexture(id);
			}
			else if(type == AssetType::Audio) {
				releaseAudio(id);
			}
		}


		void update(float deltaTime) final {

		}
			

	};

}

#endif