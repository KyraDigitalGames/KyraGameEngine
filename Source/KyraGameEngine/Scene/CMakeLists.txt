add_library(KyraScene STATIC Scene.hpp
                             Scene.cpp)
target_link_libraries(KyraScene PRIVATE KyraScripting)