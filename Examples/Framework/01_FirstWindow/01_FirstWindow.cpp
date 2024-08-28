#include <KyraGameEngine/Window.hpp>

int main(int argc, char** argv) {
		
	// Initialize the window
	kyra::WindowDescriptor windowDescriptor;
	windowDescriptor.title = "Kyra Game Engine";
	windowDescriptor.width = 1280;
	windowDescriptor.height = 720;
	
	auto window = kyra::Window::create();
	if(!window->init(windowDescriptor)) {
		return -1;
	}
	
	// Show the window
	window->show();			
	
	// Run main loop
	while(window->isOpen()) {
		window->processEvents();
	}
			
	return 0;
}
