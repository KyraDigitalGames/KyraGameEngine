#ifndef KYRAGAMEENGINE_INPUT_KEYBOARD_HPP
#define KYRAGAMEENGINE_INPUT_KEYBOARD_HPP

#include <KyraGameEngine/Window/Window.hpp>
#include <map>

namespace kyra {

	class Keyboard {

		static std::map<Key, bool> m_KeyMap;


	public:

		static void setKeyState(Key key, bool isPressed);

		static bool isPressed(Key key);

	};

}

#endif