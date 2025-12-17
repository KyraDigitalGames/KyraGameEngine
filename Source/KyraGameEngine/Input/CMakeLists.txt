add_library(KyraInput STATIC InputManager.cpp
                           InputManager.hpp
                           Keyboard.hpp
						   Keyboard.cpp)
target_compile_definitions(KyraInput PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_include_directories(KyraInput PRIVATE ${KYRA_SOURCE_DIRECTORY})