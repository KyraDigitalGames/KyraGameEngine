
#include "WindowWinAPI.hpp"

namespace kyra {
  
  LRESULT CALLBACK WindowWinAPI::eventCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    WindowWinAPI* window = reinterpret_cast<WindowWinAPI*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if(window) {
      switch(msg) {
        case WM_CLOSE:
          window->onClose.dispatch();
          return 0;
        case WM_MOUSEMOVE:
          window->onMouseMoved.dispatch(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
          return 0;
      }
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
  }
  
  WindowWinAPI::~WindowWinAPI() {
    if(m_Handle) {
      DestroyWindow(m_Handle);
    }
    if(m_ClassName != "") {
      UnregisterClass(m_ClassName.c_str(), m_ModuleHandle);
    }
  }
  
  bool WindowWinAPI::init(const WindowDescriptor& windowDescriptor) {
      
      WNDCLASSEX wcex = {0};
      wcex.cbSize = sizeof(wcex);
      wcex.style  = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
      wcex.lpfnWndProc = WindowWinAPI::eventCallback;
      wcex.hInstance = m_ModuleHandle;
      wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
      wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
      wcex.lpszClassName = windowDescriptor.className.c_str();
      
      if(!RegisterClassEx(&wcex)) {
        return false;
      }
      
      m_ClassName = windowDescriptor.className;
      
      int style = 0;
      if(windowDescriptor.fullscreen) {
        style = WS_POPUP;
      } else {
        if(windowDescriptor.borderless) {
          style = WS_POPUP;
        } else {
          style = WS_OVERLAPPEDWINDOW;
        }
      }
      
      RECT rect = {0,0,windowDescriptor.width, windowDescriptor.height};
      if(!windowDescriptor.fullscreen && !windowDescriptor.borderless) {
        AdjustWindowRect(&rect, style, 0);
      }
      
      m_Handle = CreateWindow(windowDescriptor.className.c_str(),
                              windowDescriptor.title.c_str(),
                              style,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              rect.right - rect.left, 
                              rect.bottom - rect.top,
                              NULL,
                              NULL,
                              m_ModuleHandle,
                              NULL);
                              
      if(!m_Handle) {
        return false;
      }
      
      SetWindowLongPtr(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
      
      if(!windowDescriptor.fullscreen) {
        int x = (GetSystemMetrics(SM_CXSCREEN) - rect.right - rect.left) >> 1;
        int y = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom - rect.top) >> 1;
        SetWindowPos(m_Handle, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
      }
            
    return true;
  }
  
  bool WindowWinAPI::isOpen() const {
      return IsWindow(m_Handle) && !m_ShouldClose;
  }
  
  void WindowWinAPI::processEvents() {
    MSG msg;
    while(PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  
  void WindowWinAPI::close() {
    m_ShouldClose = true;
  }
    
  void WindowWinAPI::show() {
    ShowWindow(m_Handle, SW_SHOW);
  }
    
  std::size_t WindowWinAPI::getHandle() const {
    return reinterpret_cast<std::size_t>(m_Handle);
  }

  


}