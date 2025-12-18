add_library(KyraScene STATIC Scene.hpp
                             Scene.cpp
                             Component.hpp
                             Node.hpp
                             Scene.hpp
                             ./2D/SceneRenderProcessor2D.cpp
			     ./2D/SceneRenderProcessor2D.hpp
			     ./2D/SceneSystem2D.cpp
			     ./2D/SceneSystem2D.hpp
			     ./2D/SpriteComponent.hpp
			     ./2D/SpriteComponent.cpp
			     ./2D/TransformComponent2D.hpp
			     ./2D/TransformComponent2D.cpp)
                             
target_compile_definitions(KyraScene PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_link_libraries(KyraScene PRIVATE KyraScripting)
install(TARGETS KyraScene ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)