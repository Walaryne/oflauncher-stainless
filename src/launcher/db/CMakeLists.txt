SET(DB_SOURCES
        OFSDatabase.cpp
        OFSDatabase.h)

find_package(SQLite3 REQUIRED)



find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)
find_library(SDL2_LIBRARY SDL2)

if(SDL2_LIBRARY)
    message("-- Found SDL2")
else()
    message("-- SDL2 not found, terminating")
    return()
endif()

include_directories(${SQLite3_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR})

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)



add_library(OFSdb ${DB_SOURCES})

target_link_libraries(OFSdb ${SQLite3_LIBRARIES})
#target_link_libraries(OFSdb stdc++fs sqlite3 ${SQLite3_LIBRARIES} )
