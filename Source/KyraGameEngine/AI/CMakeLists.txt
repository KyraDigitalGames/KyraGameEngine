add_library(KyraAI STATIC AIComponent.cpp
                          AIComponent.hpp
                          AIController.hpp
                          AIController.cpp
                          AIMessage.hpp
                          AIMessage.hpp
                          AIState.hpp
                          AIState.cpp
                          AIStateMachine.hpp
                          AIStateMachine.cpp)
target_compile_definitions(KyraAI PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_include_directories(KyraAI PRIVATE ${KYRA_SOURCE_DIRECTORY})
install(TARGETS KyraAI ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)