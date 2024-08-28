#ifndef KYRAGAMEENGINE_PLATFORM_WINDOWS_WINDOWWINAPI_HPP
#define KYRAGAMEENGINE_PLATFORM_WINDOWS_WINDOWWINAPI_HPP

#include <KyraGameEngine/Platform/AbstractWindow.hpp>
#include <windows.h>
#include <memory>

namespace kyra {
	
	class WindowWinAPI : public AbstractWindow {
		
		HWND m_Handle = NULL;
	
		static LRESULT CALLBACK windowEventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	
		public:
		~WindowWinAPI();
		
		static std::unique_ptr<WindowWinAPI> create();
		
		bool init(const WindowDescriptor& windowDescriptor) final;
		
		bool isOpen() const final;
		
		void processEvents() final;
		
		std::size_t getHandle() const;
		
		void show() final;
		
	};
	
	using Window = WindowWinAPI;
}

#endif