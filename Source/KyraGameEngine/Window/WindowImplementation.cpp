#include "WindowImplementation.hpp"

namespace kyra {
	Signal<> WindowEvents::onClose;
	Signal<Key> WindowEvents::onKeyUp;
	Signal<Key> WindowEvents::onKeyDown;
	Signal<MouseButton> WindowEvents::onMouseButtonPressed;
	Signal<MouseButton> WindowEvents::onMouseButtonReleased;
	Signal<int, int> WindowEvents::onSizeChanged;
	Signal<int, int> WindowEvents::onMoved;
}