
set(CMAKE_GENERATOR_PLATFORM=x86)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        OFSFacade.cpp
        OFSFacade.h
        ../shared/steam/OFSPathDiscover.cpp
        ../shared/steam/OFSPathDiscover.h
        ../shared/util/OFSUtil.cpp
        ../shared/util/OFSUtil.h)

set(DIRS_WIN
        dll_win)

set(DIRS_LINUX
        dll_linux)

add_library(client SHARED ${SOURCES})

if(WIN32)
    target_include_directories(client PRIVATE ${DIRS_WIN})
else()
    target_include_directories(client PRIVATE ${DIRS_LINUX})
endif()

set_target_properties(client PROPERTIES COMPILE_OPTIONS "-m32" LINK_FLAGS "-m32" PREFIX "")