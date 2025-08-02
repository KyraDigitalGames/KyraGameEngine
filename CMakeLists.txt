cmake_minimum_required(VERSION 3.25)

project(KyraGameEngine)

set(KYRA_MAJOR_VERSION 0)
set(KYRA_MINOR_VERSION 1)
set(KYRA_PATCH_VERSION 0)
set(KYRA_ROOT_DIRECTORY .)

set(KYRA_PLATFORM_WINDOWS)
set(KYRA_COMPILER_MINGW)

add_subdirectory(ThirdParty)
add_subdirectory(Source)
