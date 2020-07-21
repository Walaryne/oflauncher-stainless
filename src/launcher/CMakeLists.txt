

option(USE_GUI "Whether or not to use SDL2 to compile with GUI support" ON)
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
        ../shared/util/OFSUtil.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})

if(INCLUDE_RESOURCES)
    add_compile_definitions(INCLUDE_RESOURCES)
endif()

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
