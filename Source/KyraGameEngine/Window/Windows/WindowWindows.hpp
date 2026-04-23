#ifndef KYRAGAMEENGINE_WINDOW_WINDOWS_WINDOWWINDOWS_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOWS_WINDOWWINDOWS_HPP

#include <KyraGameEngine/Window/Window.hpp>
#include <KyraGameEngine/Window/WindowEvent.hpp>
#include <Windows.h>

namespace kyra {

	class WindowWindows : public Window {

		HWND m_Handle = NULL;

		static LRESULT CALLBACK eventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			switch (msg) {
			case WM_CLOSE:
				WindowEventBus::dispatch(&WindowEvent::onClose);
			}
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}

	public:
		~WindowWindows() {
			DestroyWindow(m_Handle);
			UnregisterClass("KYRA_WINDOW_CLASS", GetModuleHandle(nullptr));
		}

		[[nodiscard]] bool init(const Window::Descriptor& descriptor) final {

			WNDCLASSEX wcex = { 0 };
			wcex.cbSize = sizeof(wcex);
			wcex.hInstance = GetModuleHandle(nullptr);
			wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wcex.lpfnWndProc = WindowWindows::eventCallback;
			wcex.lpszClassName = "KYRA_WINDOW_CLASS";

			if (!RegisterClassEx(&wcex)) {
				return false;
			}

			int windowX = 0;
			int windowY = 0;
			if (descriptor.x > -1) {
				windowX = descriptor.x;
			}
			else if (descriptor.x == Window::WINDOW_POS_CENTERED) {

			}
			else if (descriptor.x == Window::WINDOW_POS_DEFAULT) {
				windowX = CW_USEDEFAULT;
			}

			if (descriptor.y > -1) {
				windowY = descriptor.y;
			}
			else if (descriptor.y == Window::WINDOW_POS_CENTERED) {

			}
			else if (descriptor.y == Window::WINDOW_POS_DEFAULT) {
				windowY = CW_USEDEFAULT;
			}

			m_Handle = CreateWindow("KYRA_WINDOW_CLASS",
				descriptor.title.c_str(),
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT,
				windowX, windowY,
				NULL,
				NULL,
				GetModuleHandle(nullptr),
				NULL);

			if (!m_Handle) {
				return false;
			}

			return true;
		}
		virtual void processEvents() final {
			MSG msg;
			while (PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		[[nodiscard]] std::size_t getHandle() const {
			return reinterpret_cast<std::size_t>(m_Handle);
		}
	};

	Window::Ptr Window::create() {
		return std::make_unique<WindowWindows>();
	}

}

#endif