
#include "WindowWinAPI.hpp"
#include <KyraGameEngine/Platform/MessageBox.hpp>
#include <format>
#include <windowsx.h>

namespace kyra {
	
	static constexpr DWORD toWinAPIStyle( WindowStyle style ) {
		return (style == WindowStyle::Window) ? WS_OVERLAPPEDWINDOW : WS_POPUP;
	}
	
	/// \todo Implement event dispatching
	LRESULT CALLBACK WindowWinAPI::windowEventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
	{
		switch(msg) {
			case WM_MOUSEMOVE:
				MouseMoveCallback.dispatch(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			break;
			case WM_SETCURSOR:
			break;
			case WM_LBUTTONDOWN:
				MouseButtonPressedCallback.dispatch( Mouse::Button::Left );
			break;
			case WM_LBUTTONUP:
				MouseButtonReleasedCallback.dispatch( Mouse::Button::Left );
			break;
			case WM_RBUTTONDOWN:
				MouseButtonPressedCallback.dispatch( Mouse::Button::Right );
			break;
			case WM_RBUTTONUP:
				MouseButtonReleasedCallback.dispatch( Mouse::Button::Right );
			break;
			case WM_MBUTTONDOWN:
				MouseButtonPressedCallback.dispatch( Mouse::Button::Middle );
			break;
			case WM_MBUTTONUP:
				MouseButtonReleasedCallback.dispatch( Mouse::Button::Middle );
			break;
			case WM_KEYUP:
			break;
			case WM_KEYDOWN:
			break;
			case WM_SYSKEYDOWN:
			break;
			case WM_CHAR:
			break;
			case WM_UNICHAR:
			break;
			case WM_SYSKEYUP:
			break;
			case WM_MOUSEWHEEL:
			break;
			case WM_ACTIVATE:
			break;
			case WM_SYSCOMMAND:
			break;
			case WM_SETFOCUS:
				FocusGainedCallback.dispatch();
			break;
			case WM_KILLFOCUS:
				FocusLostCallback.dispatch();
			break;
			case WM_CLOSE:
				WindowClosedCallback.dispatch();
			break;
			case WM_SIZE:
			break;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	
	WindowWinAPI::~WindowWinAPI() 
	{
		if(m_Handle) {
			DestroyWindow(m_Handle);
		}
		UnregisterClass("KYRA_WINDOW_CLASS", GetModuleHandle(nullptr));
	}
	
	std::unique_ptr<WindowWinAPI> WindowWinAPI::create() {
		return std::make_unique<WindowWinAPI>();
	}

	bool WindowWinAPI::init(const WindowDescriptor& windowDescriptor)  
	{
			
		HINSTANCE hInstance = GetModuleHandle(nullptr);
			
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(wcex);
		wcex.hInstance = hInstance;
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = WindowWinAPI::windowEventCallback;
		wcex.lpszClassName = "KYRA_WINDOW_CLASS";
		wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			
		if(!RegisterClassEx(&wcex)) {
			MessageBox::showError("Kyra Game Engine", std::format("Failed to register window class ( {} )", GetLastError()));			
			return false;
		}
		
		DWORD style = toWinAPIStyle(windowDescriptor.style);
		
		RECT windowRect = {0,0,windowDescriptor.width, windowDescriptor.height};
		if(windowDescriptor.style == WindowStyle::Window) {
			AdjustWindowRect(&windowRect, style, false);
		}
			
		m_Handle = CreateWindow( "KYRA_WINDOW_CLASS",
								 windowDescriptor.title.data(),
								 style,
								 CW_USEDEFAULT , CW_USEDEFAULT,
								 windowRect.right - windowRect.left, 
								 windowRect.bottom - windowRect.top,
								 NULL,
								 NULL,
								 hInstance,
								 NULL);
		
		if(!m_Handle) {
			MessageBox::showError("Kyra Game Engine", std::format("Failed to create window ( {} )", GetLastError()));
			return false;
		}
		
		if(windowDescriptor.style == WindowStyle::Window ||
		   windowDescriptor.style == WindowStyle::BorderlessWindow) 
		{
			const int windowX = (GetSystemMetrics(SM_CXSCREEN) - (windowRect.right - windowRect.left)) / 2;
			const int windowY = (GetSystemMetrics(SM_CYSCREEN) - (windowRect.bottom - windowRect.top)) / 2;
			SetWindowPos(m_Handle, HWND_TOPMOST, windowX, windowY, -1, -1, SWP_NOSIZE | SWP_NOZORDER);
		}
			
		return true;
	}
		
	bool WindowWinAPI::isOpen() const 
	{
		return IsWindow(m_Handle);
	}
		
	void WindowWinAPI::processEvents() 
	{
		MSG msg;
		while(PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
		
	std::size_t WindowWinAPI::getHandle() const 
	{
		return reinterpret_cast<std::size_t>(m_Handle);
	}
	
	void WindowWinAPI::show() 
	{
		ShowWindow(m_Handle, SW_SHOW);
	}
		
};
	
