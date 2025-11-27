#include "WindowImplementationWinAPI.hpp"
#include <KyraGameEngine/Log/Logger.hpp>

namespace kyra {

	std::unique_ptr<WindowImplementation> WindowImplementation::create() {
		return std::make_unique<WindowImplementationWinAPI>();
	}

	WindowImplementationWinAPI::~WindowImplementationWinAPI() {
		if (m_Handle) {
			DestroyWindow(m_Handle);
		}
		UnregisterClass("KYRA_WINDOW_CLASS", GetModuleHandle(nullptr));
	}

	bool WindowImplementationWinAPI::init(const WindowDescriptor& descriptor) {

		WNDCLASSEX wcex{ 0 };
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = DefWindowProc;
		wcex.hInstance = GetModuleHandle(nullptr);
		wcex.lpszClassName = "KYRA_WINDOW_CLASS";

		if (!RegisterClassEx(&wcex)) {
			KYRA_LOG_ERROR("Failed to initialise window class : " << GetLastError());
			return false;
		}

		m_Handle = CreateWindow("KYRA_WINDOW_CLASS", descriptor.title.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, descriptor.width, descriptor.height, nullptr,
			nullptr, GetModuleHandle(nullptr), nullptr);

		if (!m_Handle) {
			KYRA_LOG_ERROR("Failed to create window : " << GetLastError());
			return false;
		}
		return true;
	}

	bool WindowImplementationWinAPI::isOpen() const {
		return IsWindow(m_Handle);
	}
	
	void WindowImplementationWinAPI::processEvents() {
		MSG msg;
		while (PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	std::size_t WindowImplementationWinAPI::getHandle() const {
		return reinterpret_cast<size_t>(m_Handle);
	}

}