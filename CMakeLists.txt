cmake_minimum_required(VERSION 3.15)
SET(CMAKE_INSTALL_PREFIX bin)
project(oflauncher_stainless)

option(USE_GUI "Whether or not to use SDL2 to compile with GUI support" ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/ext/curlcpp/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(ext/curlcpp)
include_directories(${CURLCPP_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp src/gui/OFSGui.cpp src/gui/OFSGui.h src/net/OFSNet.cpp src/net/OFSNet.h)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(JSONCPP REQUIRED jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})

if(USE_GUI)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${JSONCPP_LIBRARIES}  curlcpp)
    add_compile_definitions(USE_GUI)
else()
    target_link_libraries(oflauncher_stainless PUBLIC ${JSONCPP_LIBRARIES} curlcpp)
endif()