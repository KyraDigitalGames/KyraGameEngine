#ifndef KYRAGAMEENGINE_WINDOW_WINDOW_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOW_HPP

#include <string>
#include <memory>

namespace kyra {

	class Window {

	public:
		virtual ~Window() = default;

		static constexpr int WINDOW_POS_CENTERED = -1;
		static constexpr int WINDOW_POS_DEFAULT = -2;

		struct Descriptor {
			std::string title = "Kyra Game Engine";
			int width = 800;
			int height = 600;
			int x = WINDOW_POS_CENTERED;
			int y = WINDOW_POS_CENTERED;
		};

		using Ptr = std::unique_ptr<Window>;

		static Window::Ptr create();

		virtual bool init(const Window::Descriptor& descriptor) = 0;
		virtual void processEvents() = 0;
		virtual std::size_t getHandle() const = 0;
	};

}

#endif