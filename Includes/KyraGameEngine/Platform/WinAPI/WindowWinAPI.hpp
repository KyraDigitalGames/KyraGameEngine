#ifndef KYRAGAMEENGINE_PLATFORM_WINAPI_WINDOWWINAPI_HPP
#define KYRAGAMEENGINE_PLATFORM_WINAPI_WINDOWWINAPI_HPP

#include <KyraGameEngine/Platform/IWindow.hpp>
#include <windows.h>

namespace kyra {
	
	class WindowWinAPI : public IWindow {
		
		HWND m_WindowHandle = 0;
		std::string m_ClassName = "";
		bool m_ShouldClose = false;
		
		static LRESULT CALLBACK systemEventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	
		static DWORD convertToWinAPIStyle(WindowStyle style);
	
		public:
		~WindowWinAPI();
				
		[[nodiscard]] bool create(const WindowSettings& settings) final;
		
		virtual void processEvents() final;
		
		[[nodiscard]] virtual bool isOpen() const final;
		
		virtual void close() final;
		
		virtual std::size_t getHandle() const final;
		
		virtual void show() final;
		virtual void hide() final;
		
	};
	
	using Window = WindowWinAPI;
}

#endif