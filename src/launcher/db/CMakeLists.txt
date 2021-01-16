SET(DB_SOURCES
        OFSDatabase.cpp
        OFSDatabase.h)

find_package(SQLite3 REQUIRED)

include_directories(${SQLITE_INCLUDE_DIR})

add_library(OFSdb ${DB_SOURCES})

target_link_libraries(OFSdb ${SQLite3_LIBRARIES})