add_library(KyraInput STATIC InputManager.cpp
                           InputManager.hpp
                           Keyboard.hpp
						   Keyboard.cpp)
target_include_directories(KyraInput PRIVATE ${KYRA_SOURCE_DIRECTORY})