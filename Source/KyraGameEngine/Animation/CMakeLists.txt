add_library(KyraAnimation STATIC AnimationComponent.cpp
                                 AnimationClip.hpp
                                 AnimationController.hpp
                                 AnimationController.cpp
                                 AnimationTarget.hpp
                                 AnimationTarget.cpp
                                 AnimationValue.hpp
                                 AnimationValue.cpp)
target_compile_definitions(KyraAnimation PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_include_directories(KyraAnimation PRIVATE ${KYRA_SOURCE_DIRECTORY})
install(TARGETS KyraAnimation ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)