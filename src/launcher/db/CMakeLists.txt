SET(DB_SOURCES
        OFSDatabase.cpp
        OFSDatabase.h)

find_package(SQLite3 REQUIRED)

include_directories(${SQLITE_INCLUDE_DIR})

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)


add_library(OFSdb ${DB_SOURCES})

#target_link_libraries(OFSdb ${SQLite3_LIBRARIES} Threads::Threads)
target_link_libraries(OFSdb stdc++fs sqlite3 ${SQLite3_LIBRARIES} )
