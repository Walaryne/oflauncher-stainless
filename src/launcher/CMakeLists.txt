

#option(USE_GUI "Whether or not to use SDL2 to compile with GUI support" ON)
option(STATIC_LINK "Static link the libraries included" OFF)
option(INCLUDE_RESOURCES "Use the resource header files instead of loading directly from the resource folder" ON)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        main.cpp
        main.h
        gui/OFSGuiProgBar.cpp
        gui/OFSGuiProgBar.h
        gui/OFSGuiImage.cpp
        gui/OFSGuiImage.h
        gui/OFSGuiButton.cpp
        gui/OFSGuiButton.h
        gui/OFSGuiText.cpp
        gui/OFSGuiText.h
        gui/OFSGuiTextEntry.cpp
        gui/OFSGuiTextEntry.h
        gui/OFSGuiSpinny.cpp
        gui/OFSGuiSpinny.h
        gui/OFSGuiError.cpp
        gui/OFSGuiError.h
        gui/OFSGui.cpp
        gui/OFSGui.h
        gui/OFSLayout.cpp
        gui/OFSLayout.h
        net/OFSNet.cpp
        net/OFSNet.h
        db/OFSDatabase.cpp
        db/OFSDatabase.h
        ../shared/steam/OFSPathDiscover.h
        ../shared/steam/OFSPathDiscover.cpp
        ../shared/util/OFSUtil.h
        ../shared/util/OFSUtil.cpp
        ../shared/util/md5.h
        ../shared/util/md5.cpp
        ../shared/util/json.hpp
        ../shared/util/nineSlice.cpp
        ../shared/util/nineSlice.h
        gui/OFSGuiDirButton.cpp
        gui/OFSGuiDirButton.h
        ../nativefiledialog/include/nfd.h
        ../nativefiledialog/include/nfd_common.h
        ../nativefiledialog/include/nfd_common.c
        ../nativefiledialog/include/common.h
        ../shared/util/openURL.h
        ../shared/config/OFSConfig.h
        ../shared/config/OFSConfig.cpp
        lzma/OFLZMA.cpp
        lzma/OFLZMA.h
        ../shared/steam/OFSSteam.cpp ../shared/steam/OFSSteam.h ../shared/steam/OFSSteamApp.cpp ../shared/steam/OFSSteamApp.h gui/OFSGuiThread.cpp gui/OFSGuiThread.h gameinfo/OFSGameInfo.cpp gameinfo/OFSGameInfo.h)

set(SOURCES_LINUX
        ../nativefiledialog/include/nfd_gtk.c
        ../shared/util/openURL-linux.cpp)

set(SOURCES_WIN32
        ../nativefiledialog/include/nfd_win.cpp
        ../shared/util/openURL-win.cpp)

if(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    set(SOURCES ${SOURCES} ${SOURCES_LINUX})
endif()

if (WIN32)
    set(SOURCES ${SOURCES} ${SOURCES_WIN32})
endif()

if(INCLUDE_RESOURCES)
    add_compile_definitions(INCLUDE_RESOURCES)
endif()

if(USE_GUI)
    find_path(SDL2_INCLUDE_DIR SDL.h)
    find_library(SDL2_LIBRARY SDL2)

    if(SDL2_LIBRARY)
        message("-- Found SDL2")
    else()
        message("-- SDL2 not found, terminating")
        return()
    endif()

    find_path(SDL2TTF_INCLUDE_DIR SDL2/SDL_ttf.h)
    find_library(SDL2TTF_LIBRARY SDL2_ttf)

    if(SDL2TTF_LIBRARY)
        message("-- Found SDL2_ttf")
    else()
        message("-- SDL2_tff not found, terminating")
        return()
    endif()
endif()

find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(LibLZMA REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${CURL_INCLUDE_DIRS} ${SQLITE_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS} ../nativefiledialog/include)

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_executable(${PROJECT_NAME} ${SOURCES})

if(STATIC_LINK)
    link_directories(${GTK_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${SDL2_STATIC_LIBRARIES} ${SDL2_TTF_STATIC_LIBRARIES} ${CURL_STATIC_LIBRARIES} ${SQLITE_STATIC_LIBRARIES} ${GTK3_STATIC_LIBRARIES} ${LIBLZMA_LIBRARIES})
else()
    link_directories(${GTK_LIBRARY_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} LINK_PUBLIC ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${CURL_LIBRARIES} ${SQLite3_LIBRARIES} ${GTK3_LIBRARIES} ${LIBLZMA_LIBRARIES})
endif()
