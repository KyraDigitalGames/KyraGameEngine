#ifndef KYRAGAMEENGINE_WINDOW_WINAPI_WINDOWWINAPI_HPP
#define KYRAGAMEENGINE_WINDOW_WINAPI_WINDOWWINAPI_HPP

#include <KyraGameEngine/Window/AbstractWindow.hpp>
#include <Windows.h>
#include <windowsx.h>

namespace kyra {
  
  // [TODO] High DPI Support
  class WindowWinAPI : public AbstractWindow {
    
    HWND m_Handle = NULL;
    std::string m_ClassName = "";
    const HINSTANCE m_ModuleHandle = GetModuleHandle(nullptr);
    bool m_ShouldClose = false;
    
    static LRESULT CALLBACK eventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    
    public:
    ~WindowWinAPI();
    
    bool init(const WindowDescriptor& windowDescriptor);
    
    bool isOpen() const final;
    
    void processEvents();
    
    void close();
    
    void show();
    
    std::size_t getHandle() const;
        
  };
}

#endif