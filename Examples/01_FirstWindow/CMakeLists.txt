add_executable(01_FirstWindow 01_FirstWindow.cpp)
target_link_libraries(01_FirstWindow PRIVATE opengl32 KyraGameEngine GLAD)
install(TARGETS 01_FirstWindow RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Binary)