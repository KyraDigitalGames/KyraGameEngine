#ifndef KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATION_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATION_HPP

#include <string>
#include <memory>
#include <map>
#include <functional>
#include <KyraGameEngine/Math/Vector2.hpp>

namespace kyra {

	template<class ... Args>
	class Signal {

		std::map<std::size_t, std::function<bool(Args...)>> m_Listeners;

	public:

		void connect(void* owner, std::function<bool(Args...)> func) {
			m_Listeners[reinterpret_cast<std::size_t>(owner)] = func;
		}

		void disconnect(void* owner) {
			auto it = m_Listeners.find(reinterpret_cast<std::size_t>(owner));
			if (it != m_Listeners.end()) {
				m_Listeners.erase(it);
			}
		}

		void dispatch(Args... args) {
			for (auto& listener : m_Listeners) {
				if (listener.second(args...)) {
					return;
				}
			}
		}

	};

	enum class Key {
		Unknown,
		Escape,
		Left,
		Right,
		Up,
		Down,
		Space,
		Enter,
		Back
	};

	enum class MouseButton {
		Left,
		Middle,
		Right
	};

	struct WindowDescriptor {
		std::string title = "Kyra Game Engine";
		int width = 800;
		int height = 600;
		bool fullscreen = false;
	};

	struct WindowEvents {
		static Signal<> onClose;
		static Signal<Key> onKeyUp;
		static Signal<Key> onKeyDown;
		static Signal<MouseButton> onMouseButtonPressed;
		static Signal<MouseButton> onMouseButtonReleased;
		static Signal<int, int> onSizeChanged;
		static Signal<int, int> onMoved;
	};

	class WindowImplementation {

	public:
		virtual ~WindowImplementation() = default;

		static std::unique_ptr<WindowImplementation> create();

		virtual bool init(const WindowDescriptor& descriptor) = 0;
		virtual bool isOpen() const = 0;
		virtual void processEvents() = 0;
		virtual std::size_t getHandle() const = 0;
		virtual Vector2<int> getSize() const = 0;

	};

}

#endif