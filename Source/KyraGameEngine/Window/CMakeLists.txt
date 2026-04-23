add_library(KyraWindow STATIC Window.hpp
							  Window.cpp
							  WindowSubSystem.hpp
							  WindowSubSystem.cpp
							  WindowEvent.hpp
							  ./Windows/WindowWindows.hpp
							  ./WIndows/WindowWindows.cpp)
target_include_directories(KyraWindow PRIVATE ${KYRA_SOURCE_ROOT})