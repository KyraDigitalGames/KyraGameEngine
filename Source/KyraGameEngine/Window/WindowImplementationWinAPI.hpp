#ifndef KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATIONWINAPI_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATIONWINAPI_HPP

#include "WindowImplementation.hpp"
#include <Windows.h>
#include <iostream>

namespace kyra {

	class WindowImplementationWinAPI : public WindowImplementation {


		HWND m_Handle = 0;

		static constexpr Key convertKey(WPARAM wparam) {
			switch (wparam) {
				case VK_LEFT:
					return Key::Left;
				case VK_RIGHT:
					return Key::Right;
				case VK_UP:
					return Key::Up;
				case VK_DOWN:
					return Key::Down;
				case VK_ESCAPE:
					return Key::Escape;
				case VK_SPACE:
					return Key::Space;
				case VK_ACCEPT:
					return Key::Enter;
				case VK_RETURN:
					return Key::Enter;
				case VK_BACK:
					return Key::Back;

			}
			return Key::Unknown;
		}

		static LRESULT CALLBACK eventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			switch (msg) {
				case WM_CLOSE:
					WindowEvents::onClose.dispatch();
					break;
				case WM_KEYDOWN:
					WindowEvents::onKeyDown.dispatch(convertKey(wparam));
					break;
				case WM_KEYUP:
					WindowEvents::onKeyUp.dispatch(convertKey(wparam));
					break;
				case WM_MBUTTONDOWN:
					WindowEvents::onMouseButtonPressed.dispatch(MouseButton::Middle);
					break;
				case WM_MBUTTONUP:
					WindowEvents::onMouseButtonReleased.dispatch(MouseButton::Middle);
					break;
				case WM_RBUTTONDOWN:
					WindowEvents::onMouseButtonPressed.dispatch(MouseButton::Right);
					break;
				case WM_RBUTTONUP:
					WindowEvents::onMouseButtonReleased.dispatch(MouseButton::Right);
					break;
				case WM_LBUTTONUP:
					WindowEvents::onMouseButtonReleased.dispatch(MouseButton::Left);
					break;
				case WM_LBUTTONDOWN:
					WindowEvents::onMouseButtonPressed.dispatch(MouseButton::Left);
					break;
				case WM_SIZE:
					WindowEvents::onSizeChanged.dispatch(0,0);
					break;
				case WM_MOVE:
					WindowEvents::onMoved.dispatch(0,0);
					break;
			}
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}

	public:
		~WindowImplementationWinAPI();

		bool init(const WindowDescriptor& descriptor) final;
		bool isOpen() const final;
		void processEvents() final;
		std::size_t getHandle() const final;

	};

}

#endif