#ifndef KYRAGAMEENGINE_WINDOW_WINDOW_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOW_HPP

#include "WindowImplementation.hpp"

namespace kyra {

	class Window {

		std::unique_ptr<WindowImplementation> m_Implementation;

	public:

		bool init(const WindowDescriptor& windowDescriptor);
		bool isOpen() const;
		void processEvents();
		std::size_t getHandle() const;
	};

}

#endif