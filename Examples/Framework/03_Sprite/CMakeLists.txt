add_executable(03_Sprite 03_Sprite.cpp)
target_compile_options(03_Sprite PRIVATE -Wall -O3)
target_link_libraries(03_Sprite PRIVATE KyraGameEngine)

install(TARGETS 03_Sprite RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Binary)