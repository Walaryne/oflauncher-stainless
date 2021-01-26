SET(UTIL_SOURCES
        OFSUtil.h
        OFSUtil.cpp
        md5.h
        md5.cpp
        json.hpp
        nineSlice.cpp
        nineSlice.h
        )

add_library(OFSUtil ${UTIL_SOURCES})