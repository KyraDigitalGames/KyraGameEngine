
LIST(APPEND KYRA_SRC ./Image/Image.cpp
					 ./Platform/AbstractWindow.cpp
					 ./RHI/BufferLayout.cpp)

if(WIN32)
	SET(KYRA_PLATFORM_DEFINITION KYRA_PLATFORM_WINDOWS)
	LIST(APPEND KYRA_SRC ./Platform/Windows/WindowWinAPI.cpp
						 ./Platform/Windows/MessageBox.cpp
						 ./Platform/Windows/OpenGLContextWGL.cpp
						 ./Platform/OpenGL/GLEX.cpp
						  )
endif()

if(KYRA_RENDERER_OPENGL)
	SET(KYRA_RENDERER_DEFINITION KYRA_RENDERER_OPENGL)
	LIST(APPEND KYRA_SRC  ./RHI/OpenGL/PipelineOpenGL.cpp
						  ./RHI/OpenGL/GraphicsContextOpenGL.cpp
						  ./RHI/OpenGL/CommandBufferOpenGL.cpp
						  ./RHI/OpenGL/ShaderOpenGL.cpp
						  ./RHI/OpenGL/ShaderProgramOpenGL.cpp
						  ./RHI/OpenGL/SwapChainOpenGL.cpp
						  ./RHI/OpenGL/VertexBufferOpenGL.cpp)
endif()

add_library(KyraGameEngine SHARED ${KYRA_SRC})

target_compile_options(KyraGameEngine PRIVATE -Wall -O3)
target_compile_definitions(KyraGameEngine PUBLIC ${KYRA_PLATFORM_DEFINITION} ${KYRA_RENDERER_DEFINITION})
target_include_directories(KyraGameEngine PUBLIC ${PROJECT_SOURCE_DIR}/Source)
target_link_libraries(KyraGameEngine PUBLIC opengl32)



install(TARGETS KyraGameEngine RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Binary
							   ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/Library)