SET(DB_SOURCES
        OFSDatabase.cpp
        OFSDatabase.h)

find_package(SQLite3 REQUIRED)

include_directories(${SQLITE_INCLUDE_DIR})

add_library(OFSdb ${DB_SOURCES})

target_link_libraries(OFSdb /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 ${SQLite3_LIBRARIES})
