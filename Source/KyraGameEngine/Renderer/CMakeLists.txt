set(KYRA_RENDERER_COMPILE_DEFINITION)
set(KYRA_RENDERER_LINK_LIBRARIES)

if(KYRA_RENDERER_ENABLE_OPENGL)
list(APPEND KYRA_RENDERER_COMPILE_DEFINITION KYRA_RENDERER_OPENGL)
list(APPEND KYRA_RENDERER_LINK_LIBRARIES GLAD opengl32)
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
                                Renderer.hpp
                                Renderer.cpp
                                Swapchain.hpp
                                CommandBuffer.hpp
                                RenderPass.hpp
                                RenderPass.cpp
                                RenderPassPresent.hpp
                                RenderPassPresent.cpp
                                RenderPipeline.hpp
                                RenderPipeline.cpp
                                RenderPassProcessor.hpp
                                RenderPipelineState.hpp
                                RenderPipelineState.cpp
                                VertexBuffer.hpp
                                VertexBuffer.cpp
                                ./OpenGL/RenderDeviceImplementationOpenGL.hpp
                                ./OpenGL/RenderDeviceImplementationOpenGL.cpp
                                ./OpenGL/SwapchainOpenGL.cpp
                                ./OpenGL/SwapchainOpenGL.hpp
                                ./OpenGL/CommandBufferOpenGL.hpp
                                ./OpenGL/CommandBufferOpenGL.cpp
                                ./OpenGL/RenderPipelineStateOpenGL.hpp
                                ./OpenGL/RenderPipelineStateOpenGL.cpp
                                ./OpenGL/VertexBufferOpenGL.cpp
                                ./OpenGL/VertexBufferOpenGL.hpp
                                ./Vulkan/RenderDeviceImplementationVulkan.hpp
                                ./Vulkan/RenderDeviceImplementationVulkan.cpp
                                ./Vulkan/SwapchainVulkan.cpp
                                ./Vulkan/SwapchainVulkan.hpp
                                ./Vulkan/CommandBufferVulkan.hpp
                                ./Vulkan/CommandBufferVulkan.cpp
                                ./Vulkan/RenderPipelineStateVulkan.hpp
                                ./Vulkan/RenderPipelineStateVulkan.cpp
                                ./Vulkan/VertexBufferVulkan.cpp
                                ./Vulkan/VertexBufferVulkan.hpp)
target_include_directories(KyraRenderer PRIVATE ${KYRA_SOURCE_DIRECTORY})
target_compile_definitions(KyraRenderer PRIVATE ${KYRA_RENDERER_COMPILE_DEFINITION})
target_link_libraries(KyraRenderer PRIVATE KyraLog ${KYRA_RENDERER_LINK_LIBRARIES} Vulkan::Vulkan)