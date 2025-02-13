#ifndef KYRAGAMEENGINE_WINDOW_ABSTRACTWINDOW_HPP
#define KYRAGAMEENGINE_WINDOW_ABSTRACTWINDOW_HPP

#include <KyraGameEngine/Messaging/Signal.hpp>
#include <string>

namespace kyra {
  
  // [TODO] Exchange fullscreen/borderless with flags
  struct WindowDescriptor {
    std::string title = "Kyra Game Engine";
    std::string className = "KYRA_WINDOW_CLASS";
    int width = 800;
    int height = 600;
    bool fullscreen = false;
    bool borderless = false;
  };
  
  class AbstractWindow {
    
    public:
    virtual ~AbstractWindow() = default;
    
    virtual bool init(const WindowDescriptor& windowDescriptor) = 0;
    virtual bool isOpen() const = 0;
    virtual void processEvents() = 0;
    virtual void show() = 0;
    virtual void close() = 0;
    virtual std::size_t getHandle() const = 0;
    
    Signal<void()> onClose;
    Signal<void(int,int)> onMouseMoved;
    
  };
  
}

#endif