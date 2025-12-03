add_library(KyraGameModule STATIC GameModule.hpp
                                  GameModule.cpp
                                  ActorFactory.hpp
                                  ActorRegistry.hpp
                                  RenderPassProcessorFactory.hpp
                                  RenderPassProcessorRegistry.hpp)
target_include_directories(KyraGameModule PRIVATE ${KYRA_SOURCE_DIRECTORY})
target_link_libraries(KyraGameModule PRIVATE KyraRenderer KyraScripting)