SET(GUI_SOURCES
        OFSGuiProgBar.h
        OFSGuiProgBar.cpp
        OFSGuiImage.cpp
        OFSGuiImage.h
        OFSGuiButton.cpp
        OFSGuiButton.h
        OFSGuiText.cpp
        OFSGuiText.h
        OFSGuiTextEntry.cpp
        OFSGuiTextEntry.h
        OFSGuiSpinny.cpp
        OFSGuiSpinny.h
        OFSGuiError.cpp
        OFSGuiError.h
        OFSGui.cpp
        OFSGui.h
        OFSLayout.cpp
        OFSLayout.h
        OFSGuiDirButton.cpp
        OFSGuiDirButton.h
        OFSGuiThread.cpp
        OFSGuiThread.h)


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


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})

add_library(OFSGui ${GUI_SOURCES})

target_link_libraries(OFSGui ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY})