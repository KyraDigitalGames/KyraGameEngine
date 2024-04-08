add_executable(01_TriangleExample 01_TriangleExample.cpp)

if(MINGW)	
target_compile_options(KyraPlatform PRIVATE -Wall -O3)
endif()

target_link_libraries(01_TriangleExample PRIVATE KyraFramework KyraLog KyraPlatform)

install(TARGETS 01_TriangleExample RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)