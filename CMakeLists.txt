cmake_minimum_required(VERSION 3.15)
SET(CMAKE_INSTALL_PREFIX bin)
SET(EXECUTABLE_OUTPUT_PATH .)
project(oflauncher_stainless)

if(WIN32)
    #looking online, checking the size of the void pointer
    #is the best way of seeing if its 64 or 32 bit lol
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        add_subdirectory(src/launcher)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        add_subdirectory(src/facade)
    endif()
else()
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CPP_COMPILER clang++)

    add_subdirectory(src/launcher)
    add_subdirectory(src/facade)
endif()