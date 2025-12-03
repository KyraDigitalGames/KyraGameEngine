add_library(Game SHARED AIPadActor.cpp
                        AIPadActor.hpp
                        BallActor.hpp
                        BallActor.cpp
                        PlayerPadActor.cpp
                        PlayerPadActor.hpp
                        SimpleRenderPassProcessor.hpp
                        SimpleRenderPassProcessor.cpp
			PongModule.hpp
			PongModule.cpp)
target_link_libraries(Game PRIVATE KyraGameEngine)
INSTALL(TARGETS Game RUNTIME DESTINATION ${KYRA_GAME_INSTALL_DIR})