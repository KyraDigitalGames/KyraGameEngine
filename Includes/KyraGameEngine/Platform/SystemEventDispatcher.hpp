#ifndef KYRAGAMEENGINE_PLATFORM_SYSTEMEVENTDISPATCHER_HPP
#define KYRAGAMEENGINE_PLATFORM_SYSTEMEVENTDISPATCHER_HPP

#include <KyraGameEngine/Math/Size2.hpp>
#include <KyraGameEngine/Math/Vector2.hpp>

#include "Mouse.hpp"
#include "Keyboard.hpp"

#include <vector>
#include <functional>
#include <algorithm>
#include <cstdint>

namespace kyra {
	
	using SystemEventFunc = std::function<bool()>;
	using MouseMoveEventFunc = std::function<bool(const Vector2<int32_t>)>;
	using MouseButtonEventFunc = std::function<bool(Mouse::Button)>;
	using KeyEventFunc = std::function<bool(Keyboard::Key)>;
	using MouseWheelEventFunc = std::function<bool(int32_t)>;
	using TextEventFunc = std::function<bool(char)>;
	using WindowSizeFunc = std::function<bool(const Size2<int32_t>)>;
	
	class SystemEventDispatcher {
		
		std::vector<SystemEventFunc> m_CloseEventHandler;
		std::vector<MouseButtonEventFunc> m_MouseButtonPressedEventHandler;
		std::vector<MouseButtonEventFunc> m_MouseButtonReleasedEventHandler;
		std::vector<MouseMoveEventFunc> m_MouseMovedEventHandler;
		std::vector<MouseWheelEventFunc> m_MouseWheelEventHandler;
		std::vector<KeyEventFunc> m_KeyPressedEventHandler;
		std::vector<KeyEventFunc> m_KeyReleasedEventHandler;
		
		public:
		virtual ~SystemEventDispatcher() = default;
		
		void registerCloseHandler( SystemEventFunc func ) {
			m_CloseEventHandler.emplace_back(func);
		}
		
		void registerMouseButtonPressedHandler( MouseButtonEventFunc func ) {
			m_MouseButtonPressedEventHandler.emplace_back(func);
		}
		
		void registerMouseButtonReleasedHandler( MouseButtonEventFunc func ) {
			m_MouseButtonReleasedEventHandler.emplace_back(func);
		}
		
		void registerMouseMovedHandler( MouseButtonEventFunc func ) {
			m_MouseButtonReleasedEventHandler.emplace_back(func);
		}
		
		void registerMouseWheelHandler( MouseWheelEventFunc func ) {
			m_MouseWheelEventHandler.emplace_back(func);
		}
		
		void registerKeyPressedHandler( KeyEventFunc func ) {
			m_KeyPressedEventHandler.emplace_back(func);
		}
		
		void registerKeyReleasedHandler( KeyEventFunc func ) {
			m_KeyReleasedEventHandler.emplace_back(func);
		}
		
		bool injectCloseEvent() {
			auto it = std::find_if(m_CloseEventHandler.begin(), m_CloseEventHandler.end(), [](auto& entry) {
				return entry();
			});
			return (it != m_CloseEventHandler.end());
		} 
		
		bool injectMouseButtonPressed(Mouse::Button button) {
			auto it = std::find_if(m_MouseButtonPressedEventHandler.begin(), m_MouseButtonPressedEventHandler.end(), [&](auto& entry) {
				return entry(button);
			});
			return (it != m_MouseButtonPressedEventHandler.end());
		}
		
		bool injectMouseButtonReleased(Mouse::Button button) {
			auto it = std::find_if(m_MouseButtonReleasedEventHandler.begin(), m_MouseButtonReleasedEventHandler.end(), [&](auto& entry) {
				return entry(button);
			});
			return (it != m_MouseButtonReleasedEventHandler.end());
		}
		
		bool injectMouseMoved(const Vector2<int32_t>& vec) {
			auto it = std::find_if(m_MouseMovedEventHandler.begin(), m_MouseMovedEventHandler.end(), [&](auto& entry) {
				return entry(vec);
			});
			return (it != m_MouseMovedEventHandler.end());
		}
		
		bool injectMouseWheel(int32_t delta) {
			auto it = std::find_if(m_MouseWheelEventHandler.begin(), m_MouseWheelEventHandler.end(), [&](auto& entry) {
				return entry(delta);
			});
			return (it != m_MouseWheelEventHandler.end());
		}
		
		bool injectKeyPressed(Keyboard::Key key) {
			auto it = std::find_if(m_KeyPressedEventHandler.begin(), m_KeyPressedEventHandler.end(), [&](auto& entry) {
				return entry(key);
			});
			return (it != m_KeyPressedEventHandler.end());
		}
		
		bool injectKeyReleased(Keyboard::Key key) {
			auto it = std::find_if(m_KeyReleasedEventHandler.begin(), m_KeyReleasedEventHandler.end(), [&](auto& entry) {
				return entry(key);
			});
			return (it != m_KeyReleasedEventHandler.end());
		}
		
		
		
	};
}

#endif