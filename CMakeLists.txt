cmake_minimum_required(VERSION 3.15)
SET(CMAKE_INSTALL_PREFIX bin)
project(oflauncher_stainless)

option(USE_GUI "Whether or not to use SDL2 to compile with GUI support" ON)
option(STATIC_LINK "Static link the libraries included" OFF)
option(DRAW_WINDOW "Have the client.so try to draw on the engine window" OFF)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/main.cpp
        src/main.h
        src/gui/OFSGuiImage.cpp
        src/gui/OFSGuiImage.h
        src/gui/OFSGuiButton.cpp
        src/gui/OFSGuiButton.h
        src/gui/OFSGuiText.cpp
        src/gui/OFSGuiText.h
        src/gui/OFSGuiTextEntry.cpp
        src/gui/OFSGuiTextEntry.h
        src/gui/OFSGuiSpinny.cpp
        src/gui/OFSGuiSpinny.h
        src/gui/OFSGuiError.cpp
        src/gui/OFSGuiError.h
        src/gui/OFSGui.cpp
        src/gui/OFSGui.h
        src/gui/OFSLayout.cpp
        src/gui/OFSLayout.h
        src/net/OFSNet.cpp
        src/net/OFSNet.h
        src/db/OFSDatabase.cpp
        src/db/OFSDatabase.h
        src/steam/OFSPathDiscover.h
        src/steam/OFSPathDiscover.cpp
        src/util/OFSUtil.h
        src/util/OFSUtil.cpp)

set(SOURCES_FACADE
        src/facade/OFSFacade.cpp
        src/facade/OFSFacade.h)

add_library(client SHARED ${SOURCES_FACADE})
set_target_properties(client PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" PREFIX "")


add_executable(${PROJECT_NAME} ${SOURCES})

if(USE_GUI)
    find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)
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

    add_compile_definitions(USE_GUI)
endif()

find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${CURL_INCLUDE_DIRS} ${SQLITE_INCLUDE_DIRS})

if(DRAW_WINDOW)
    add_compile_definitions(DRAW_WINDOW)
    TARGET_LINK_LIBRARIES(client PUBLIC ${LIB32SDL2_LIBRARY})
endif()

if(STATIC_LINK)
    if(USE_GUI)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${SDL2_STATIC_LIBRARIES} ${SDL2_TTF_STATIC_LIBRARIES} ${CURL_STATIC_LIBRARIES} ${SQLITE_STATIC_LIBRARIES})
    else()
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${CURL_STATIC_LIBRARIES} ${SQLITE_STATIC_LIBRARIES})
    endif()
else()
    if(USE_GUI)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${CURL_LIBRARIES} ${SQLite3_LIBRARIES})
    else()
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${CURL_LIBRARIES} ${SQLite3_LIBRARIES})
    endif()
endif()
