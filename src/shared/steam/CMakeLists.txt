SET(STEAM_SOURCES
        OFSPathDiscover.h
        OFSPathDiscover.cpp
        OFSSteam.cpp
        OFSSteam.h
        OFSSteamApp.cpp
        OFSSteamApp.h)
add_library(OFSSteam ${STEAM_SOURCES})
target_include_directories(OFSSteam PUBLIC ../util)
