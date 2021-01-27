

option(STATIC_LINK "Static link the libraries included" OFF)

set(SOURCES
        main.cpp
        main.h)

set(OFS_LIBRARIES
        hashlib2plus
        OFSGui
        OFSdb
        OFSNet
        OFSGameInfo
        OFSMD5
        OFSLaunchOpt
        OFSConfig
        OFSSteam
        OFSUtil
        nfd
        minlzlib)

if(UNIX)
    find_package(PkgConfig REQUIRED)
endif()

add_subdirectory(hashlib2plus)
add_subdirectory(gui)
add_subdirectory(db)
add_subdirectory(net)
add_subdirectory(nativefiledialog)
add_subdirectory(gameinfo)
add_subdirectory(MD5)
add_subdirectory(launchopt)

add_executable(${PROJECT_NAME} ${SOURCES})


TARGET_LINK_LIBRARIES(${PROJECT_NAME} LINK_PUBLIC  ${OFS_LIBRARIES})

