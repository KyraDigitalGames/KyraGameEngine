#include <KyraGameEngine/Platform/WinAPI/WindowWinAPI.hpp>
#include <KyraGameEngine/Log/Logger.hpp>

#include <windowsx.h>

namespace kyra {
	
	LRESULT CALLBACK WindowWinAPI::systemEventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		
		WindowWinAPI* window = reinterpret_cast<WindowWinAPI*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if(window) {
			switch(msg) {
				case WM_CLOSE:
					if(!window->injectCloseEvent()) {
						window->close();
					}
					return 0;
				case WM_LBUTTONDOWN:
					if(window->injectMouseButtonPressed(Mouse::Button::Left)) {
						return 0;
					}
					break;
				case WM_RBUTTONDOWN:
					if(window->injectMouseButtonPressed(Mouse::Button::Right)) {
						return 0;
					}
					break;
				case WM_MBUTTONDOWN:
					if(window->injectMouseButtonPressed(Mouse::Button::Middle)) {
						return 0;
					}
					break;
				case WM_LBUTTONUP:
					if(window->injectMouseButtonReleased(Mouse::Button::Left)) {
						return 0;
					}
					break;				
				case WM_MBUTTONUP:
					if(window->injectMouseButtonReleased(Mouse::Button::Middle)) {
						return 0;
					}
					break;				
				case WM_RBUTTONUP:
					if(window->injectMouseButtonReleased(Mouse::Button::Right)) {
						return 0;
					}
					break;				
				case WM_MOUSEMOVE:
				{
					if(window->injectMouseMoved({GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam)})) {
						return 0;
					}
				}
				break;				
				case WM_MOUSEWHEEL:
					if(window->injectMouseWheel(GET_WHEEL_DELTA_WPARAM(wparam) / 120)) {
						return 0;
					}
				break;
				case WM_KEYUP:
					return 0;
				case WM_KEYDOWN:
					return 0;
				case WM_CHAR:
					return 0;
				case WM_SETFOCUS:
					return 0;
				case WM_KILLFOCUS:
					return 0;
			}
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	
	DWORD WindowWinAPI::convertToWinAPIStyle(WindowStyle style) {
		if(style == WindowStyle::Window) {
			return WS_OVERLAPPEDWINDOW;
		}
		return WS_POPUP;
	}
	
	WindowWinAPI::~WindowWinAPI() {
		if(m_WindowHandle) {
			DestroyWindow(m_WindowHandle);
		}
		if(m_ClassName != "") {
			UnregisterClass(m_ClassName.c_str(), GetModuleHandle(nullptr));
		}
	}
		
		
	bool WindowWinAPI::create(const WindowSettings& settings) {
			
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEX));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.hInstance = GetModuleHandle(nullptr);
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = settings.className.c_str();
		wcex.lpfnWndProc = WindowWinAPI::systemEventCallback;
			
		if(!RegisterClassEx(&wcex)) {
			KYRA_LOG_ERROR(WindowWinAPI::create, "Failed to register window class ( " << GetLastError() << " )");
			return false;
		}
			
		m_ClassName = settings.className;
			
		DWORD style = convertToWinAPIStyle(settings.style);
		RECT rectangle {0,0,settings.size.getWidth(), settings.size.getHeight()};
		if(settings.style == WindowStyle::Window) {
			AdjustWindowRect(&rectangle, style, false);
		}
			
		m_WindowHandle = CreateWindow( settings.className.c_str(),
									   settings.title.c_str(),
									   style,
									   CW_USEDEFAULT,
									   CW_USEDEFAULT,
									   rectangle.right - rectangle.left,
									   rectangle.bottom - rectangle.top,
									   NULL,
									   NULL,
									   GetModuleHandle(nullptr), 
									   NULL);
		if(!m_WindowHandle) {
			KYRA_LOG_ERROR(WindowWinAPI::create, "Failed to create window ( " << GetLastError() << " )");
			return false;
		}
			
		SetWindowLongPtr(m_WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		
		GetWindowRect(m_WindowHandle, &rectangle);
		const int screenX = (GetSystemMetrics(SM_CXSCREEN) - rectangle.right ) / 2;
		const int screenY = (GetSystemMetrics(SM_CYSCREEN) - rectangle.bottom ) / 2;
		SetWindowPos(m_WindowHandle, m_WindowHandle, screenX, screenY, -1, -1, SWP_NOSIZE | SWP_NOZORDER);	
		return true;
	}
		
	void WindowWinAPI::processEvents() {
		MSG msg;
		while(PeekMessage(&msg, m_WindowHandle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
		
	bool WindowWinAPI::isOpen() const {
		return IsWindow(m_WindowHandle) && !m_ShouldClose;
	}
		
	void WindowWinAPI::close() {
		m_ShouldClose = true;
	}
	
	std::size_t WindowWinAPI::getHandle() const {
		return reinterpret_cast<std::size_t>(m_WindowHandle);
	}
	
	void WindowWinAPI::show() {
		ShowWindow(m_WindowHandle, SW_SHOW);
	}
	
	void WindowWinAPI::hide() {
		ShowWindow(m_WindowHandle, SW_HIDE);
	}
	
}