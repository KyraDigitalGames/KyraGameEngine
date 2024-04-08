add_library(KyraLog SHARED Logger.cpp
						   LogStreamConsole.cpp
						   LogStreamFile.cpp)
						   
if(MINGW)	
target_compile_options(KyraLog PRIVATE -Wall -O3)
endif()

install(TARGETS KyraLog EXPORT KyraGameEngine-targets
						RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
						ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)