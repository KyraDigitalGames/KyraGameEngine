add_library(KyraScripting STATIC Actor.hpp
                                 Actor.cpp)
install(TARGETS KyraScripting ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)