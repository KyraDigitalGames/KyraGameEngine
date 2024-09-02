#include <KyraGameEngine/Platform.hpp>
#include <KyraGameEngine/Log/Log.hpp>
#include <iostream>
#include <format>

int main(int argc, char** argv) {
		
	kyra::Log::info("Initialise window");
	kyra::WindowDescriptor windowDescriptor;
	windowDescriptor.title = "Kyra Game Engine";
	windowDescriptor.width = 1280;
	windowDescriptor.height = 720;
	
	auto window = kyra::Window::create();
	if(!window->init(windowDescriptor)) {
		return -1;
	}
	
	kyra::Log::info("Initialise event callbacks");
	
	auto mouseMoveCallback = kyra::MouseMoveCallback.connect([](int x, int y){
		kyra::Log::info(std::format("Mouse moved: {} {}", x, y));		
		return true;
	});
	
	auto windowClosedCallback = kyra::WindowClosedCallback.connect([](){
		kyra::Log::info("Window closed");		
		return true;		
	});
	
	kyra::Log::info("Show window");
	window->show();			
	
	kyra::Log::info("Run main loop");
	while(window->isOpen()) {
		window->processEvents();
	}
			
	return 0;
}
