add_library(KyraApplication STATIC Application.cpp
                           Application.hpp)
target_include_directories(KyraApplication PRIVATE ${KYRA_SOURCE_DIRECTORY})
target_compile_definitions(KyraApplication PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_link_libraries(KyraApplication PRIVATE KyraLog KyraWindow)