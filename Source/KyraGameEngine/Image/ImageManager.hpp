#ifndef KYRAGAMEENGINE_IMAGE_IMAGEMANAGER_HPP
#define KYRAGAMEENGINE_IMAGE_IMAGEMANAGER_HPP

#include <KyraGameEngine/Core/System.hpp>
#include "Image.hpp"
#include <string>
#include <map>

namespace kyra {

	class ImageManager : public System {

		std::map<std::string, Image> m_ImageMap;

	public:

		Image* load(const std::string& file) {
			auto it = m_ImageMap.find(file);
			if (it == m_ImageMap.end()) {
				if (!m_ImageMap[file].load(file)) {
					return nullptr;
				}
			}
			return &m_ImageMap[file];
		}

		void release(Image* image) {
			auto it = m_ImageMap.find(image->getPath());
			if (it == m_ImageMap.end()) {
				return;
			}
			m_ImageMap.erase(it);
		}

		void update(float deltaTime) {

		}

	};

}

#endif