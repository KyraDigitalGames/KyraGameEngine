add_library(KyraImage STATIC ImageManager.cpp
                             ImageManager.hpp
                             Image.hpp
                             Image.cpp
                             stb_image.h
                             stb_image_resize2.h
                             stb_image_write.h)
target_compile_definitions(KyraImage PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_include_directories(KyraImage PRIVATE ${KYRA_SOURCE_DIRECTORY})
install(TARGETS KyraImage ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)