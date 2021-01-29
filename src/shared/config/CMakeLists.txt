SET(CONFIG_SOURCES
        OFSConfig.h
        OFSConfig.cpp)

add_library(OFSConfig ${CONFIG_SOURCES})
target_include_directories(OFSConfig PUBLIC ../util)
