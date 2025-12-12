#include "Keyboard.hpp"

namespace kyra {

	std::map<Key, bool> Keyboard::m_KeyMap = {
		{Key::Escape, false},
		{Key::Left, false},
		{Key::Right, false},
		{Key::Up, false},
		{Key::Down, false}
	};

	void Keyboard::setKeyState(Key key, bool isPressed) {
		m_KeyMap[key] = isPressed;
	}

	bool Keyboard::isPressed(Key key) {
		return m_KeyMap[key];
	}
}