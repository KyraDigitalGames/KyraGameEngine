add_executable(KyraPlayer KyraPlayer.cpp)
target_link_libraries(KyraPlayer PRIVATE KyraGameEngine)

install(TARGETS KyraPlayer RUNTIME DESTINATION ${KYRA_GAME_INSTALL_DIR})