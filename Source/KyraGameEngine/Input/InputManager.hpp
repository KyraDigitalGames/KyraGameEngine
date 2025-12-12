#ifndef KYRAGAMEENGINE_INPUT_INPUTMANAGER_HPP
#define KYRAGAMEENGINE_INPUT_INPUTMANAGER_HPP

#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Core/System.hpp>
#include "Keyboard.hpp"

namespace kyra {

	struct InputManagerDescriptor {
		Window* window = nullptr;
	};

	class InputManager : public System {

	public:
		bool init(InputManagerDescriptor& descriptor) {

			if (!descriptor.window) {
				return false;
			}

			kyra::WindowEvents::onKeyDown.connect(this, [](kyra::Key key) {
				Keyboard::setKeyState(key, true);
				return false;
			});

			kyra::WindowEvents::onKeyUp.connect(this, [](kyra::Key key) {
				Keyboard::setKeyState(key, false);
				return false;
			});

			return true;
		}

	};

}

#endif