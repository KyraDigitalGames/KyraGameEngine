
#include "WindowWinAPI.hpp"

namespace kyra {
	
	/// \todo Implement event dispatching
	LRESULT CALLBACK WindowWinAPI::windowEventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	
	WindowWinAPI::~WindowWinAPI() {
		if(m_Handle) {
			DestroyWindow(m_Handle);
		}
		UnregisterClass("KYRA_WINDOW_CLASS", GetModuleHandle(nullptr));
	}
	
	std::unique_ptr<WindowWinAPI> WindowWinAPI::create() {
		return std::make_unique<WindowWinAPI>();
	}

	/// \todo Adjust window rect
	/// \todo Add window style support
	/// \todo Center the window if window style is Window or BorderlessWindow
	bool WindowWinAPI::init(const WindowDescriptor& windowDescriptor)  {
			
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
			return false;
		}
			
		m_Handle = CreateWindow( "KYRA_WINDOW_CLASS",
								 windowDescriptor.title.data(),
								 WS_OVERLAPPEDWINDOW,
								 CW_USEDEFAULT , CW_USEDEFAULT,
								 windowDescriptor.width, 
								 windowDescriptor.height,
								 NULL,
								 NULL,
								 hInstance,
								 NULL);
		
		if(!m_Handle) {
			return false;
		}
			
		return true;
	}
		
	bool WindowWinAPI::isOpen() const {
		return IsWindow(m_Handle);
	}
		
	void WindowWinAPI::processEvents() {
		MSG msg;
		while(PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
		
	std::size_t WindowWinAPI::getHandle() const {
		return reinterpret_cast<std::size_t>(m_Handle);
	}
	
	void WindowWinAPI::show() {
		ShowWindow(m_Handle, SW_SHOW);
	}
		
};
	
