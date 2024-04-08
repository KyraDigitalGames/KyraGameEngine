
cmake_minimum_required(VERSION 3.25)

project(KyraGameEngine)

set(KYRA_COMPILE_DEFINITIONS "")
if(KYRA_RENDERER_DX11)
	message(STATUS "KYRA_INFO: USE DIRECTX11 RENDERER")
	add_compile_definitions(KYRA_RENDERER_DX11)
	set(KYRA_COMPILE_DEFINITIONS "-DKYRA_RENDERER_DX11")
else()
	set(KYRA_RENDERER_GL ON)
	message(STATUS "KYRA_INFO: USE OPENGL RENDERER")
	add_compile_definitions(KYRA_RENDERER_GL)
	set(KYRA_COMPILE_DEFINITIONS "-DKYRA_RENDERER_GL")
endif()


set(CMAKE_CXX_STANDARD 20)
if(MSVC)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# TODO: Remove this
include_directories(${PROJECT_SOURCE_DIR}/Includes)

# TODO: Remove this
link_directories(${PROJECT_SOURCE_DIR}/lib)

# Build Kyra Game Engine
add_subdirectory(Source)

# Build examples
add_subdirectory(Examples)


# Export the KyraGameEngine interface
#
# Usage in your own project: 
# find_package(KyraGameEngine 0.1.0 REQUIRED)
# target_link_libraries(YOUR_TARGET_NAME PRIVATE KyraGameEngine::KyraGameEngine) 
#

include(CMakePackageConfigHelpers)

configure_package_config_file(KyraGameEngine.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/KyraGameEngineConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/KyraGameEngine
)
  
write_basic_package_version_file(KyraGameEngineConfigVersion.cmake
  VERSION 0.1.0
  COMPATIBILITY SameMajorVersion
  ARCH_INDEPENDENT)
 
add_library(KyraGameEngine INTERFACE)
target_link_libraries(KyraGameEngine INTERFACE KyraFramework KyraLog KyraPlatform)
target_include_directories(KyraGameEngine INTERFACE ${CMAKE_INSTALL_PREFIX}/include) 
target_compile_definitions(KyraGameEngine INTERFACE ${KYRA_COMPILE_DEFINITIONS})

install(TARGETS KyraGameEngine
	EXPORT KyraGameEngine-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
 
install(EXPORT  KyraGameEngine-targets
        FILE KyraGameEngineTargets.cmake
        NAMESPACE KyraGameEngine::
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/KyraGameEngine
)
 
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/KyraGameEngineConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/KyraGameEngineConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/KyraGameEngine )

install(DIRECTORY ${PROJECT_SOURCE_DIR}/Includes/KyraGameEngine DESTINATION ${CMAKE_INSTALL_PREFIX}/include)