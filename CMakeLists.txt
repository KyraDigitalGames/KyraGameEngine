cmake_minimum_required(VERSION 3.25)

project(KyraGameEngine)

option(KYRA_RENDERER_OPENGL "Enables the OpenGL renderer" ON)

#TODO: REMOVE THIS AND ADD THE INCLUDE TO THE TARGETS
include_directories(Source)

add_subdirectory(Source)
add_subdirectory(Examples)