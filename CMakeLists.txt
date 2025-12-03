# Require at least CMake version 3.25 to ensure modern features are available
CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

# Define the project name
PROJECT(KyraGameEngine)

# Set engine version numbers
SET(KYRA_MAJOR_VERSION 0)
SET(KYRA_MINOR_VERSION 1)
SET(KYRA_PATCH_VERSION 0)

# Print a status message showing the engine version during configuration
MESSAGE(STATUS "Building KyraGameEngine ${KYRA_MAJOR_VERSION}.${KYRA_MINOR_VERSION}.${KYRA_PATCH_VERSION}")

# Build options for enabling/disabling different rendering backends
OPTION(KYRA_RENDERER_ENABLE_OPENGL "Enables the OpenGL rendering device" ON)
OPTION(KYRA_RENDERER_ENABLE_VULKAN "Enables the Vulkan rendering device" OFF)
OPTION(KYRA_RENDERER_ENABLE_METAL "Enables the Metal rendering device" OFF)
OPTION(KYRA_RENDERER_ENABLE_DIRECTX11 "Enables the DirectX11 rendering device" OFF)
OPTION(KYRA_RENDERER_ENABLE_DIRECTX12 "Enables the DirectX12 rendering device" OFF)

find_package(Vulkan REQUIRED)

# Define root and source directory paths
SET(KYRA_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
SET(KYRA_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source")

# Define Installaation Directory
if(NOT DEFINED ${KYRA_GAME_INSTAL_DIR})
set(KYRA_GAME_INSTALL_DIR ${KYRA_ROOT}/Binary)
endif()
MESSAGE(STATUS "Installation Directory: ${KYRA_GAME_INSTALL_DIR}")


# Add subdirectories to the build
# 'ThirdParty' contains third party libraries
# 'Source' contains the main engine implementation
# 'Examples' contains demo applications or sample projects
ADD_SUBDIRECTORY(ThirdParty)
ADD_SUBDIRECTORY(Source)
ADD_SUBDIRECTORY(Examples)