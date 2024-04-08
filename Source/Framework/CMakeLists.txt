add_library(KyraFramework SHARED Application.cpp)
						   
if(MINGW)	
target_compile_options(KyraPlatform PRIVATE -Wall -O3)
endif()

if(KYRA_RENDERER_DX11)
SET(KYRA_FRAMEWORK_LIBRARIES d3d11 DXGI)
else()
SET(KYRA_FRAMEWORK_LIBRARIES opengl32 KyraGLEX)
endif()

target_link_libraries(KyraFramework PUBLIC ${KYRA_FRAMEWORK_LIBRARIES} KyraPlatform KyraLog)

install(TARGETS KyraFramework EXPORT KyraGameEngine-targets
							  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
							  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)