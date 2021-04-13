

option(STATIC_LINK "Static link the libraries included" OFF)
option(SHOW_CMD_ON_WINDOWS "Show the command prompt when running the windows binary." OFF)

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

if(WIN32)
    if(SHOW_CMD_ON_WINDOWS)
        message("Showing command prompt in windows build.")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
        target_compile_definitions(${PROJECT_NAME} PUBLIC SHOW_CMD_ON_WINDOWS)

        
    else()
        message("Hiding command prompt on windows.")
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
    endif(SHOW_CMD_ON_WINDOWS)
endif()
TARGET_LINK_LIBRARIES(${PROJECT_NAME} LINK_PUBLIC  ${OFS_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} PUBLIC ${OFS_LIBRARIES})
