add_library(KyraGLEX SHARED WGL.cpp)
						   
if(MINGW)	
target_compile_options( KyraGLEX PRIVATE -Wall -O3)
endif()

install(TARGETS KyraGLEX EXPORT KyraGameEngine-targets
						RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
						ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)