set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.9)
SET(CMAKE_INSTALL_PREFIX bin)
SET(EXECUTABLE_OUTPUT_PATH .)
project(oflauncher_stainless)
add_subdirectory(src/shared/config)
add_subdirectory(src/shared/steam)
add_subdirectory(src/shared/util)
add_subdirectory(src/shared/minlzma)

add_subdirectory(src/launcher)

