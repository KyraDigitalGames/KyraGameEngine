#include "Window.hpp"
#include <KyraGameEngine/Log/Logger.hpp>

#include <assert.h>

#include <KyraGameEngine/Debug/Profiling.hpp>

namespace kyra {

	bool Window::init(const WindowDescriptor& windowDescriptor) {
		KYRA_PROFILE_FUNCTION();
		KYRA_LOG_INFO("Initialise Window");
		KYRA_LOG_INFO("Title: " << windowDescriptor.title);
		KYRA_LOG_INFO("Width: " << windowDescriptor.width);
		KYRA_LOG_INFO("Height: " << windowDescriptor.height);
		m_Implementation = WindowImplementation::create();
		return m_Implementation->init(windowDescriptor);
	}

	bool Window::isOpen() const {
		KYRA_PROFILE_FUNCTION();
		assert(m_Implementation);
		if (m_Implementation) {
			return m_Implementation->isOpen();
		}
		return false;
	}

	void Window::update(float deltaTime) {
		KYRA_PROFILE_FUNCTION();
		assert(m_Implementation);
		if (m_Implementation) {
			m_Implementation->processEvents();
		}
	}

	std::size_t Window::getHandle() const {
		KYRA_PROFILE_FUNCTION();
		assert(m_Implementation);
		if (m_Implementation) {
			return m_Implementation->getHandle();
		}
		return 0;
	}

	Vector2<int> Window::getSize() const {
		KYRA_PROFILE_FUNCTION();
		assert(m_Implementation);
		if (m_Implementation) {
			return m_Implementation->getSize();
		}
		return { -1,-1 };
	}

	void Window::requestClose() {
		if (!WindowEvents::onCloseRequested.dispatch()) {
			WindowEvents::onClose.dispatch();
		}
	}

}