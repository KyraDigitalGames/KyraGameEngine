add_library(KyraLog STATIC Logger.cpp
                           Logger.hpp
                           LogMessage.hpp)
target_include_directories(KyraLog PRIVATE ${KYRA_SOURCE_DIRECTORY})