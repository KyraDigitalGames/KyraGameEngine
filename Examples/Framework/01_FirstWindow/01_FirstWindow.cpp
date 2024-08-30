#include <KyraGameEngine/Platform.hpp>
#include <iostream>

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
	
	auto mouseMoveCallback = kyra::MouseMoveCallback.connect([](int x, int y){
		std::cout << "Mouse moved " << x <<" " << y << std::endl;		
		return true;
	});
	
	auto windowClosedCallback = kyra::WindowClosedCallback.connect([](){
		std::cout << "Window closed" << std::endl;		
		return true;		
	});
	
	// Show the window
	window->show();			
	
	// Run main loop
	while(window->isOpen()) {
		window->processEvents();
	}
			
	return 0;
}
