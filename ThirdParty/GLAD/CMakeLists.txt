
add_library(GLAD STATIC ./src/glad.c
                        ./src/glad_wgl.c)
target_include_directories(GLAD PUBLIC ./include)