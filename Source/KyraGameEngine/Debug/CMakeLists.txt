add_library(KyraDebug STATIC Profiling.cpp
                           Profiling.hpp)
target_compile_definitions(KyraDebug PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_include_directories(KyraDebug PRIVATE ${KYRA_SOURCE_DIRECTORY})