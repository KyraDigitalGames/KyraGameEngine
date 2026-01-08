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
			return std::move(TextureAsset::Handle(&m_TextureAssets[textureAsset.id], this));
		}

		TextureAsset* getTextureAsset(AssetId id) {
			auto it = m_TextureAssets.find(id);
			if (it != m_TextureAssets.end()) {
				return &it->second;
			}
			return nullptr;
		}
				
		void update(float deltaTime) final {

		}

		void release(AssetId id) final {
			auto it = m_TextureAssets.find(id);
			if (it != m_TextureAssets.end()) {
				if (it->second.refCount < 1) {
					m_TextureAssets.erase(it);
				}
			}
		}

	};

}

#endif