#include "AbstractWindow.hpp"

namespace kyra {
	
	Callback<int,int> MouseMoveCallback;
	Callback<Keyboard::Key> KeyPressedCallback;
	Callback<Keyboard::Key> KeyReleasedCallback;
	Callback<Mouse::Button> MouseButtonPressedCallback;
	Callback<Mouse::Button> MouseButtonReleasedCallback;
	Callback<char> TextEnteredCallback;
	Callback<void> FocusLostCallback;
	Callback<void> FocusGainedCallback;
	Callback<int, int> WindowSizeChangedCallback;
	Callback<void> WindowClosedCallback;

}