add_library(KyraLog STATIC Logger.cpp
                           Logger.hpp
                           LogMessage.hpp)
target_compile_definitions(KyraLog PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_include_directories(KyraLog PRIVATE ${KYRA_SOURCE_DIRECTORY})