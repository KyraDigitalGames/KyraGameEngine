add_library(KyraAsset STATIC Asset.hpp
                             AssetManager.hpp
                             AssetManager.cpp
                             AssetOwner.hpp
                             AssetLoaderInterface.hpp
                             ./Audio/AudioAsset.hpp
                             ./Audio/AudioLoaderInterface.hpp
                             ./Audio/AudioLoaderWAV.hpp
                             ./Audio/AudioLoaderWAV.cpp
                             ./Texture/ImageLoaderInterface.hpp
                             ./Texture/ImageLoaderSTB.hpp
                             ./Texture/ImageLoaderSTB.cpp
                             ./Texture/TextureAsset.hpp
                             ./Texture/ImageAsset.hpp)
target_include_directories(KyraAsset PRIVATE ${KYRA_SOURCE_DIRECTORY})
target_compile_definitions(KyraAsset PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})

install(TARGETS KyraAsset ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)