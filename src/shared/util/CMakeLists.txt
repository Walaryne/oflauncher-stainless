SET(UTIL_SOURCES
		OFFilesystem.h
        OFSUtil.h
        OFSUtil.cpp
        md5.h
        md5.cpp
        json.hpp
        nineSlice.cpp
        nineSlice.h
        )

add_library(OFSUtil ${UTIL_SOURCES})
