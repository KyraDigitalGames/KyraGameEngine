add_subdirectory(Window)
add_subdirectory(Renderer)

add_library(KyraGameEngine INTERFACE)
target_include_directories(KyraGameEngine INTERFACE ${KYRA_SOURCE_ROOT})
target_link_libraries(KyraGameEngine INTERFACE KyraWindow KyraRenderer)