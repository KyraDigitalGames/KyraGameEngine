set(KYRA_RENDERER_COMPILE_DEFINITION)
set(KYRA_RENDERER_LINK_LIBRARIES)

if(KYRA_RENDERER_ENABLE_OPENGL)
list(APPEND KYRA_RENDERER_COMPILE_DEFINITION KYRA_RENDERER_OPENGL)
list(APPEND KYRA_RENDERER_LINK_LIBRARIES opengl32)
MESSAGE(STATUS "OpenGL Render Device: Enabled")
else()
MESSAGE(STATUS "OpenGL Render Device: Enabled")
endif()
if(KYRA_RENDERER_ENABLE_VULKAN)
list(APPEND KYRA_RENDERER_COMPILE_DEFINITION KYRA_RENDERER_VULKAN_ENABLED)
MESSAGE(STATUS "Vulkan Render Device: Enabled")
else()
MESSAGE(STATUS "Vulkan Render Device: Disabled")
endif()


add_library(KyraRenderer STATIC RenderDeviceImplementation.hpp
                                RenderDeviceImplementationOpenGL.hpp
                                RenderDeviceImplementationOpenGL.cpp
                                Renderer.hpp
                                Renderer.cpp
                                Swapchain.hpp
                                SwapchainOpenGL.cpp
                                SwapchainOpenGL.hpp
                                CommandBuffer.hpp
                                CommandBufferOpenGL.hpp
                                CommandBufferOpenGL.cpp)
target_include_directories(KyraRenderer PRIVATE ${KYRA_SOURCE_DIRECTORY})
target_compile_definitions(KyraRenderer PRIVATE ${KYRA_RENDERER_COMPILE_DEFINITION})
target_link_libraries(KyraRenderer PRIVATE KyraLog ${KYRA_RENDERER_LINK_LIBRARIES})