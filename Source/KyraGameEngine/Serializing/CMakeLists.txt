add_library(KyraSerialization STATIC BinaryReader.cpp
                                     BinaryReader.hpp
                                     BinaryWriter.cpp
                                     BinaryWriter.hpp
                                     Serializable.hpp
                                     )
target_include_directories(KyraSerialization PRIVATE ${KYRA_SOURCE_DIRECTORY})