#include "AssetManager.hpp"

namespace kyra {

	template<> 
	bool AssetManager::isLoadingQueueEmpty<TextureAsset>() const {
		return m_TextureLoadingQueue.empty();
	}

	template<>
	std::vector<AssetId>& AssetManager::getLoadingQueue<TextureAsset>() {
		return m_TextureLoadingQueue;
	}

	template<>
	bool AssetManager::isLoadingQueueEmpty<AudioAsset>() const {
		return m_AudioLoadingQueue.empty();
	}

	template<>
	std::vector<AssetId>& AssetManager::getLoadingQueue<AudioAsset>() {
		return m_AudioLoadingQueue;
	}


}