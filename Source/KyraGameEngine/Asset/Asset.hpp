#ifndef KYRAGAMEENGINE_ASSET_ASSET_HPP
#define KYRAGAMEENGINE_ASSET_ASSET_HPP

#include <vector>
#include <KyraGameEngine/Image/Image.hpp>

namespace kyra {

	using AssetId = std::uint32_t;
	static constexpr AssetId INVALID_ASSET_ID = 0;

	class AssetOwner {
		public:
		virtual ~AssetOwner() = default;

		virtual void release(AssetId id) = 0;
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
		
			Handle() = default;

			Handle(const Handle& handle) {
				asset = handle.asset;
				if (asset) {
					asset->refCount++;
				}
			}

			Handle(Asset* asset, AssetOwner* owner) : asset(asset) {
				if (asset) {
					asset->owner = owner;
					asset->refCount++;
				}
			}

			~Handle() {
				if (asset) {
					asset->refCount--;
					if (asset->refCount < 1 && asset->owner) {
						asset->owner->release(asset->id);
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



}


#endif