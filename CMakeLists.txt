cmake_minimum_required(VERSION 3.15)
SET(CMAKE_INSTALL_PREFIX bin)
SET(EXECUTABLE_OUTPUT_PATH .)
project(oflauncher_stainless)

if(WIN32)
    
else()
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CPP_COMPILER clang++)

    add_subdirectory(src/launcher)
endif()