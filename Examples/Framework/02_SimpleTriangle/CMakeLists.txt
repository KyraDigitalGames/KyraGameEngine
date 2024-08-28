add_executable(02_SimpleTriangle 02_SimpleTriangle.cpp)
target_compile_options(02_SimpleTriangle PRIVATE -Wall -O3)
target_link_libraries(02_SimpleTriangle PRIVATE KyraGameEngine)

install(TARGETS 02_SimpleTriangle RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Binary)