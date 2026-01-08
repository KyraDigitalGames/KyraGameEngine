#ifndef KYRAGAMEENGINE_WINDOW_WINDOW_HPP
#define KYRAGAMEENGINE_WINDOW_WINDOW_HPP

#include "WindowImplementation.hpp"
#include <KyraGameEngine/Core/System.hpp>

namespace kyra {

	class Window : public System {

		std::unique_ptr<WindowImplementation> m_Implementation;

	public:

		bool init(const WindowDescriptor& windowDescriptor);
		bool isOpen() const;
		void update(float deltaTime);
		std::size_t getHandle() const;
		Vector2<int> getSize() const;
		void requestClose();
	};

}

#endif