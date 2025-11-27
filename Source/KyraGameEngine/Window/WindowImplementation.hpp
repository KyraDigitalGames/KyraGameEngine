#ifndef KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATION_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATION_HPP

#include <string>
#include <memory>

namespace kyra {

	struct WindowDescriptor {
		std::string title = "Kyra Game Engine";
		int width = 800;
		int height = 600;
	};

	class WindowImplementation {

	public:
		virtual ~WindowImplementation() = default;

		static std::unique_ptr<WindowImplementation> create();

		virtual bool init(const WindowDescriptor& descriptor) = 0;
		virtual bool isOpen() const = 0;
		virtual void processEvents() = 0;
		virtual std::size_t getHandle() const = 0;

	};

}

#endif