add_executable(TriangleExample TriangleExample.cpp)
target_link_libraries(TriangleExample PRIVATE KyraGameEngine)

install(TARGETS TriangleExample RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/Examples/TriangleExample)