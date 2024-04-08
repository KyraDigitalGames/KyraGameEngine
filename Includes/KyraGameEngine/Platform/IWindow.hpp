#ifndef KYRAGAMEENGINE_PLATFORM_IWINDOW_HPP
#define KYRAGAMEENGINE_PLATFORM_IWINDOW_HPP

#include <KyraGameEngine/Math/Size2.hpp>
#include <KyraGameEngine/Platform/SystemEventDispatcher.hpp>
#include <string>

namespace kyra {
	
	enum class WindowStyle {
		Window,
		BorderlessWindow,
		Fullscreen,
		NativeFullscreen
	};
	
	struct WindowSettings {
		std::string title = "Kyra Game Engine";
		std::string className = "KYRA_WINDOW_CLASS";
		Size2<int32_t> size = {1280, 720};
		WindowStyle style = WindowStyle::Window;
	};
	
	class IWindow : public SystemEventDispatcher {
		
		public:
		
		[[nodiscard]] virtual bool create(const WindowSettings& settings) = 0;
		virtual void processEvents() = 0;
		[[nodiscard]] virtual bool isOpen() const = 0;
		virtual void close() = 0;
		virtual std::size_t getHandle() const = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
	};
	
}

#endif