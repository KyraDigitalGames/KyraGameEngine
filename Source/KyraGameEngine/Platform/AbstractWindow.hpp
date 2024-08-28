#ifndef KYRAGAMEENGINE_PLATFORM_ABSTRACTWINDOW_HPP
#define KYRAGAMEENGINE_PLATFORM_ABSTRACTWINDOW_HPP

#include <string_view>

namespace kyra {
	
	struct WindowDescriptor {
		std::string_view title = "Kyra Game Engine";
		int width = 800;
		int height = 600;
	};
	
	class AbstractWindow {
		
		public:
		virtual ~AbstractWindow() = default;
		
		virtual bool init(const WindowDescriptor& windowDescriptor) = 0;
		virtual bool isOpen() const = 0;
		virtual void processEvents() = 0;
		virtual std::size_t getHandle() const = 0;
		virtual void show() = 0;
	};
}

#endif