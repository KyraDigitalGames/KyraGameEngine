#ifndef KYRAGAMEENGINE_PLATFORM_ABSTRACTWINDOW_HPP
#define KYRAGAMEENGINE_PLATFORM_ABSTRACTWINDOW_HPP

#include "Mouse.hpp"
#include "Keyboard.hpp"

#include <KyraGameEngine/Core/Callback/Callback.hpp>

#include <string_view>
#include <map>
#include <algorithm>
#include <memory>



namespace kyra {
	
	extern Callback<int,int> MouseMoveCallback;
	extern Callback<Keyboard::Key> KeyPressedCallback;
	extern Callback<Keyboard::Key> KeyReleasedCallback;
	extern Callback<Mouse::Button> MouseButtonPressedCallback;
	extern Callback<Mouse::Button> MouseButtonReleasedCallback;
	extern Callback<char> TextEnteredCallback;
	extern Callback<void> FocusLostCallback;
	extern Callback<void> FocusGainedCallback;
	extern Callback<int, int> WindowSizeChangedCallback;
	extern Callback<void> WindowClosedCallback;
		
	enum class WindowStyle {
		Window,
		BorderlessWindow,
		Fullscreen,
		NativeFullscreen
	};
	
	struct WindowDescriptor {
		std::string_view title = "Kyra Game Engine";
		int width = 800;
		int height = 600;
		WindowStyle style = WindowStyle::Window;
	};
	
	class AbstractWindow {
		
		public:
		virtual ~AbstractWindow() = default;
		
		virtual bool init(const WindowDescriptor& windowDescriptor) = 0;
		virtual bool isOpen() const = 0;
		virtual void processEvents() = 0;
		virtual std::size_t getHandle() const = 0;
		virtual void show() = 0;
	};
}

#endif