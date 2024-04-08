add_library(KyraPlatform SHARED ./WinAPI/WindowWinAPI.cpp)
	
if(MINGW)	
target_compile_options(KyraPlatform PRIVATE -Wall -O3)
endif()

target_link_libraries(KyraPlatform PRIVATE KyraLog)

install(TARGETS KyraPlatform EXPORT KyraGameEngine-targets
							 RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
							 ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)