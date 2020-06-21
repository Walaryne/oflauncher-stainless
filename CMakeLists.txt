cmake_minimum_required(VERSION 3.15)
SET(CMAKE_INSTALL_PREFIX bin)
project(oflauncher_stainless)

option(USE_GUI "Whether or not to use SDL2 to compile with GUI support" ON)
option(STATIC_LINK "Static link the libraries included" OFF)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/main.cpp
        src/main.h
        src/gui/OFSGui.cpp
        src/gui/OFSGui.h
        src/net/OFSNet.cpp
        src/net/OFSNet.h
        src/db/OFSDatabase.cpp
        src/db/OFSDatabase.h)

add_executable(${PROJECT_NAME} ${SOURCES})

INCLUDE(FindPkgConfig)

if(USE_GUI)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    add_compile_definitions(USE_GUI)
endif()

pkg_search_module(CURL REQUIRED libcurl)
pkg_search_module(SQLITE REQUIRED sqlite3)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS} ${SQLITE_INCLUDE_DIRS})
if(STATIC_LINK)
    if(USE_GUI)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${SDL2_STATIC_LIBRARIES} ${CURL_STATIC_LIBRARIES} ${SQLITE_STATIC_LIBRARIES})
    else()
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${CURL_STATIC_LIBRARIES} ${SQLITE_STATIC_LIBRARIES})
    endif()
else()
    if(USE_GUI)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${CURL_LIBRARIES} ${SQLITE_LIBRARIES})
    else()
        TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${CURL_LIBRARIES} ${SQLITE_LIBRARIES})
    endif()
endif()
