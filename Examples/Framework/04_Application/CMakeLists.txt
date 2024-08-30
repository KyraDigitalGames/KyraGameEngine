add_executable(04_Application 04_Application.cpp)
target_compile_options(04_Application PRIVATE -Wall -O3)
target_link_libraries(04_Application PRIVATE KyraGameEngine)

install(TARGETS 04_Application RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Binary)