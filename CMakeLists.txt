cmake_minimum_required(VERSION 3.25)

project(KyraGameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(KYRA_RENDERER_OPENGL "Enables the OpenGL renderer" ON)

find_package(Vulkan REQUIRED)

add_subdirectory(Source)
add_subdirectory(Examples)