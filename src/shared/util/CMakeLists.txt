SET(UTIL_SOURCES
		OFFilesystem.h
        OFSUtil.h
        OFSUtil.cpp
        md5.h
        md5.cpp
        json.hpp
        openURL.h
        OFSRunExe.h
        )

set(UTIL_SOURCES_LINUX
        openURL-linux.cpp)

set(UTIL_SOURCES_WIN32
        openURL-win.cpp)

if(UNIX)
    set(UTIL_SOURCES ${UTIL_SOURCES} ${UTIL_SOURCES_LINUX})
endif()

if (WIN32)
    set(UTIL_SOURCES ${UTIL_SOURCES} ${UTIL_SOURCES_WIN32})
endif()

add_library(OFSUtil ${UTIL_SOURCES})
