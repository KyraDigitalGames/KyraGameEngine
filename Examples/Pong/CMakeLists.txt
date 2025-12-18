add_executable(Pong Pong.cpp)
target_link_libraries(Pong PRIVATE KyraGameEngine)

install(TARGETS Pong RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/Examples/Pong)
install(DIRECTORY Assets DESTINATION ${CMAKE_INSTALL_PREFIX}/Examples/Pong)