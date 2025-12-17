add_library(KyraScene STATIC Scene.hpp
                             Scene.cpp
                             Component.hpp
                             Node.hpp
                             Scene.hpp
                             TransformComponent.hpp
                             TransformSystem.hpp)
                             
target_compile_definitions(KyraScene PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_link_libraries(KyraScene PRIVATE KyraScripting)