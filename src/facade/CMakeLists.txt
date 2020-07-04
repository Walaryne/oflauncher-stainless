
if(UNIX)
        set(CMAKE_C_FLAGS -m32)
        set(CMAKE_CXX_FLAGS -m32)
        set(CMAKE_FIND_ROOT_PATH /usr/lib32)

        set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()
set(CMAKE_CXX_STANDARD 17)

set(DLL_DIR_WIN
        dll_win)

set(DLL_DIR_LINUX
        dll_linux)

if(WIN32)
    set(DLL_DIR ${DLL_DIR_WIN})
else()
    set(DLL_DIR ${DLL_DIR_LINUX})
endif()

set(SOURCES
        OFSFacade.cpp
        OFSFacade.h
        ../shared/steam/OFSPathDiscover.cpp
        ../shared/steam/OFSPathDiscover.h
        ../shared/util/OFSUtil.cpp
        ../shared/util/OFSUtil.h
        ${DLL_DIR}/OFSLoadLib.cpp
        ${DLL_DIR}/OFSLoadLib.h)

add_library(client SHARED ${SOURCES})
target_include_directories(client PRIVATE ${DLL_DIR})

set_target_properties(client PROPERTIES PREFIX "")