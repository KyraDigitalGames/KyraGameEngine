#include "Window.hpp"
#include <KyraGameEngine/Log/Logger.hpp>

#include <assert.h>

namespace kyra {

	bool Window::init(const WindowDescriptor& windowDescriptor) {
		KYRA_LOG_INFO("Initialise Window");
		KYRA_LOG_INFO("Title: " << windowDescriptor.title);
		KYRA_LOG_INFO("Width: " << windowDescriptor.width);
		KYRA_LOG_INFO("Height: " << windowDescriptor.height);
		m_Implementation = WindowImplementation::create();
		return m_Implementation->init(windowDescriptor);
	}

	bool Window::isOpen() const {
		assert(m_Implementation);
		if (m_Implementation) {
			return m_Implementation->isOpen();
		}
		return false;
	}

	void Window::update(float deltaTime) {
		assert(m_Implementation);
		if (m_Implementation) {
			m_Implementation->processEvents();
		}
	}

	std::size_t Window::getHandle() const {
		assert(m_Implementation);
		if (m_Implementation) {
			return m_Implementation->getHandle();
		}
		return 0;
	}

}