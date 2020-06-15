cmake_minimum_required(VERSION 3.15)
SET(CMAKE_INSTALL_PREFIX bin)
project(oflauncher_stainless)

option(USE_GUI "Whether or not to use SDL2 to compile with GUI support" ON)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp src/gui/OFSGui.cpp src/gui/OFSGui.h src/net/OFSNet.cpp src/net/OFSNet.h)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(JSONCPP REQUIRED jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})

if(USE_GUI)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${JSONCPP_LIBRARIES} curl)
    add_compile_definitions(USE_GUI)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC ${JSONCPP_LIBRARIES} curl)
endif()