SET(NFD_SOURCES
        include/nfd.h
        include/nfd_common.h
        include/nfd_common.c
        include/common.h)

set(NFD_SOURCES_LINUX
        include/nfd_gtk.c)

set(NFD_SOURCES_WIN32
        include/nfd_win.cpp)

if(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
    set(NFD_SOURCES ${NFD_SOURCES} ${NFD_SOURCES_LINUX})

    link_directories(${GTK_LIBRARY_DIRS})
    ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})


endif()

if (WIN32)
    set(NFD_SOURCES ${NFD_SOURCES} ${NFD_SOURCES_WIN32})
endif()

add_library(nfd ${NFD_SOURCES})

if(UNIX)
    TARGET_LINK_LIBRARIES(nfd ${GTK3_LIBRARIES})
endif()