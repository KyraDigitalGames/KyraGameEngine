add_executable(01_FirstWindow 01_FirstWindow.cpp)
target_compile_options(01_FirstWindow PRIVATE -Wall -O3)
target_link_libraries(01_FirstWindow PRIVATE KyraGameEngine)

install(TARGETS 01_FirstWindow RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Binary)