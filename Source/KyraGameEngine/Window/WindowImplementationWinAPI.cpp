#include "WindowImplementationWinAPI.hpp"
#include <KyraGameEngine/Log/Logger.hpp>
#include <KyraGameEngine/Debug/Profiling.hpp>

namespace kyra {

	std::unique_ptr<WindowImplementation> WindowImplementation::create() {
		KYRA_PROFILE_FUNCTION();
		return std::make_unique<WindowImplementationWinAPI>();
	}

	WindowImplementationWinAPI::~WindowImplementationWinAPI() {
		ChangeDisplaySettings(nullptr, 0);
		KYRA_PROFILE_FUNCTION();
		if (m_Handle) {
			DestroyWindow(m_Handle);
		}
		UnregisterClass("KYRA_WINDOW_CLASS", GetModuleHandle(nullptr));
	}

	bool WindowImplementationWinAPI::init(const WindowDescriptor& descriptor) {
		KYRA_PROFILE_FUNCTION();
		WNDCLASSEX wcex{ 0 };
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = WindowImplementationWinAPI::eventCallback;
		wcex.hInstance = GetModuleHandle(nullptr);
		wcex.lpszClassName = "KYRA_WINDOW_CLASS";

		if (!RegisterClassEx(&wcex)) {
			KYRA_LOG_ERROR("Failed to initialise window class : " << GetLastError());
			return false;
		}

		if (descriptor.fullscreen) {
			HMONITOR monitor = MonitorFromWindow(m_Handle, MONITOR_DEFAULTTOPRIMARY);
			MONITORINFOEX mi = {};
			mi.cbSize = sizeof(mi);
			GetMonitorInfo(monitor, &mi);
			int width = mi.rcMonitor.right - mi.rcMonitor.left;
			int height = mi.rcMonitor.bottom - mi.rcMonitor.top;
			DEVMODE dm = {};
			dm.dmSize = sizeof(dm);
			dm.dmPelsWidth = width;
			dm.dmPelsHeight = height;
			dm.dmBitsPerPel = 32;
			dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
			LONG result = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
			switch (result) {
			case DISP_CHANGE_SUCCESSFUL:
				KYRA_LOG_INFO("DISP_CHANGE_SUCCESSFUL");
				break;
			case DISP_CHANGE_BADDUALVIEW:
				KYRA_LOG_INFO("DISP_CHANGE_BADDUALVIEW");
				break;
			case DISP_CHANGE_BADFLAGS:
				KYRA_LOG_INFO("DISP_CHANGE_BADFLAGS");
				break;
			case DISP_CHANGE_BADMODE:
				KYRA_LOG_INFO("DISP_CHANGE_BADMODE");
				break;
			case DISP_CHANGE_BADPARAM:
				KYRA_LOG_INFO("DISP_CHANGE_BADPARAM");
				break;
			case DISP_CHANGE_FAILED:
				KYRA_LOG_INFO("DISP_CHANGE_FAILED");
				break;
			case DISP_CHANGE_NOTUPDATED:
				KYRA_LOG_INFO("DISP_CHANGE_NOTUPDATED");
				break;
			case DISP_CHANGE_RESTART:
				KYRA_LOG_INFO("DISP_CHANGE_RESTART");
				break;
			}
			m_Handle = CreateWindow("KYRA_WINDOW_CLASS", descriptor.title.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr,
				nullptr, GetModuleHandle(nullptr), nullptr);
			SetForegroundWindow(m_Handle);
			SetFocus(m_Handle);
		} else {
			m_Handle = CreateWindow("KYRA_WINDOW_CLASS", descriptor.title.c_str(), WS_POPUP | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT, descriptor.width, descriptor.height, nullptr,
				nullptr, GetModuleHandle(nullptr), nullptr);

			if (!m_Handle) {
				KYRA_LOG_ERROR("Failed to create window : " << GetLastError());
				return false;
			}
		}
		return true;
	}

	bool WindowImplementationWinAPI::isOpen() const {
		KYRA_PROFILE_FUNCTION();
		return IsWindow(m_Handle);
	}
	
	void WindowImplementationWinAPI::processEvents() {
		KYRA_PROFILE_FUNCTION();
		MSG msg;
		while (PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	std::size_t WindowImplementationWinAPI::getHandle() const {
		KYRA_PROFILE_FUNCTION();
		return reinterpret_cast<size_t>(m_Handle);
	}

}