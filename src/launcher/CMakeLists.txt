

option(STATIC_LINK "Static link the libraries included" OFF)

set(SOURCES
        main.cpp
        main.h)
include_directories(../shared/util)
set(OFS_LIBRARIES
	libzstd_static
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
        OFImportSVN
        nfd
        minlzlib)

if(UNIX)
    find_package(PkgConfig REQUIRED)
endif()

find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

add_subdirectory(zstd/build/cmake)
add_subdirectory(hashlib2plus)
add_subdirectory(gui)
add_subdirectory(db)
add_subdirectory(net)
add_subdirectory(nativefiledialog)
add_subdirectory(gameinfo)
add_subdirectory(MD5)
add_subdirectory(launchopt)
add_subdirectory(importsvn)

add_executable(${PROJECT_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} LINK_PUBLIC  ${OFS_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} PUBLIC ${OFS_LIBRARIES})
