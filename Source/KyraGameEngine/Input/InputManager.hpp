#ifndef KYRAGAMEENGINE_INPUT_INPUTMANAGER_HPP
#define KYRAGAMEENGINE_INPUT_INPUTMANAGER_HPP

#include <KyraGameEngine/Window/Window.hpp>

namespace kyra {

	struct InputManagerDescriptor {
		Window* window = nullptr;
	};

	class InputManager {

	public:
		bool init(InputManagerDescriptor& descriptor) {

			if (!descriptor.window) {
				return false;
			}

			kyra::WindowEvents::onKeyDown.connect(this, [&](kyra::Key key) {
				return false;
			});

			kyra::WindowEvents::onKeyUp.connect(this, [&](kyra::Key key) {
				return false;
			});

			return true;
		}

	};

}

#endif