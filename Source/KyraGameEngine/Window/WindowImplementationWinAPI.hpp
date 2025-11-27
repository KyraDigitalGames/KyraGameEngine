#ifndef KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATIONWINAPI_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOWIMPLEMENTATIONWINAPI_HPP

#include "WindowImplementation.hpp"
#include <Windows.h>

namespace kyra {

	class WindowImplementationWinAPI : public WindowImplementation {

		HWND m_Handle = 0;

	public:
		~WindowImplementationWinAPI();

		bool init(const WindowDescriptor& descriptor) final;
		bool isOpen() const final;
		void processEvents() final;
		std::size_t getHandle() const final;

	};

}

#endif