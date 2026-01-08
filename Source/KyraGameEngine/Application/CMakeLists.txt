add_library(KyraApplication STATIC Application.cpp
                                   Application.hpp
                                   Game3D.hpp
                                   Game3D.cpp
                                   Game2D.hpp
                                   Game3D.cpp)
target_include_directories(KyraApplication PRIVATE ${KYRA_SOURCE_DIRECTORY})
target_compile_definitions(KyraApplication PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_link_libraries(KyraApplication PRIVATE KyraLog KyraWindow)

install(TARGETS KyraApplication ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)