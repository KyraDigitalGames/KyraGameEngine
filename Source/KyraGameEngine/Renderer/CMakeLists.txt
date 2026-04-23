add_library(KyraRenderer STATIC ./RHI/RHIBuffer.hpp
								./RHI/RHICommandBuffer.hpp
								./RHI/RHICommandQueue.hpp
								./RHI/RHIDevice.hpp
								./RHI/RHIFrameBuffer.hpp
								./RHI/RHIPipelineLayout.hpp
								./RHI/RHIPipelineState.hpp
								./RHI/RHIRenderPass.hpp
								./RHI/RHIShader.hpp
								./RHI/RHISwapChain.hpp
								./RHI/OpenGL/RHIBufferOpenGL.hpp
								./RHI/OpenGL/RHIBufferOpenGL.cpp
								./RHI/OpenGL/RHICommandBufferOpenGL.hpp
								./RHI/OpenGL/RHICommandBufferOpenGL.cpp
								./RHI/OpenGL/RHICommandQueueOpenGL.hpp
								./RHI/OpenGL/RHICommandQueueOpenGL.cpp
								./RHI/OpenGL/RHIDeviceOpenGL.hpp
								./RHI/OpenGL/RHIDeviceOpenGL.cpp
								./RHI/OpenGL/RHIFrameBufferOpenGL.hpp
								./RHI/OpenGL/RHIPipelineLayoutOpenGL.hpp
								./RHI/OpenGL/RHIPipelineLayoutOpenGL.cpp
								./RHI/OpenGL/RHIPipelineStateOpenGL.hpp
								./RHI/OpenGL/RHIPipelineStateOpenGL.cpp
								./RHI/OpenGL/RHIRenderPassOpenGL.hpp
								./RHI/OpenGL/RHIRenderPassOpenGL.cpp
								./RHI/OpenGL/RHIShaderOpenGL.hpp
								./RHI/OpenGL/RHIShaderOpenGL.cpp
								./RHI/OpenGL/RHISwapChainOpenGL.hpp
								./RHI/OpenGL/RHISwapChainOpenGL.cpp
								./RHI/OpenGL/OpenGL.hpp
								./RHI/OpenGL/OpenGL.cpp
								./RHI/OpenGL/OpenGLContext.hpp
								./RHI/OpenGL/Windows/WGL.hpp
								./RHI/OpenGL/Windows/WGL.cpp
								./RHI/OpenGL/Windows/OpenGLContextWGL.hpp
								./RHI/OpenGL/Windows/OpenGLContextWGL.cpp)
target_include_directories(KyraRenderer PRIVATE ${KYRA_SOURCE_ROOT})
target_link_libraries(KyraRenderer PUBLIC opengl32)