
#include <KyraGameEngine/Window/WindowEvent.hpp>
#include <KyraGameEngine/Window/Windows/WindowWindows.hpp>

class TestApplication {


	class EventHandler : public kyra::WindowEvent::Handler {

		bool m_IsQuitRequested = false;

	public:

		bool onClose() final {
			m_IsQuitRequested = true;
			return false;
		}

		bool isQuitRequested() const {
			return m_IsQuitRequested;
		}

	};
	EventHandler m_EventHandler;

public:

	int run(int argc, char** argv) {

		kyra::Window::Descriptor windowDescriptor;
		windowDescriptor.x = kyra::Window::WINDOW_POS_DEFAULT;
		windowDescriptor.y = kyra::Window::WINDOW_POS_DEFAULT;

		kyra::Window::Ptr window = kyra::Window::create();
		if (!window->init(windowDescriptor)) {
			return -1;
		}

		while (!m_EventHandler.isQuitRequested()) {
			window->processEvents();
		}

		return 0;
	}

};

int main(int argc, char** argv) {
	return TestApplication().run(argc, argv);
}