add_library(KyraAudio STATIC AudioBuffer.cpp
                             AudioBuffer.hpp
                             AudioController.hpp
                             AudioController.cpp
                             AudioListener.hpp
                             AudioListener.cpp
                             AudioSource.hpp
                             AudioSource.cpp
                             AudioDeviceImplementation.hpp
                             AudioComponent.hpp
                             AudioComponent.cpp
                             ./XAudio2/AudioBufferXAudio2.hpp
                             ./XAudio2/AudioBufferXAudio2.cpp
                             ./XAudio2/AudioListenerXAudio2.hpp
                             ./XAudio2/AudioListenerXAudio2.cpp
                             ./XAudio2/AudioSourceXAudio2.hpp
                             ./XAudio2/AudioSourceXAudio2.cpp
                             ./XAudio2/AudioDeviceImplementationXAudio2.hpp
                             ./XAudio2/AudioDeviceImplementationXAudio2.cpp)
target_compile_definitions(KyraAudio PRIVATE ${KYRA_GLOBAL_COMPILE_DEFINITIONS})
target_include_directories(KyraAudio PRIVATE ${KYRA_SOURCE_DIRECTORY})
install(TARGETS KyraAudio ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib)