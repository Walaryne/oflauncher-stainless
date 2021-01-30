SET(NET_SOURCES
        OFSNet.cpp
        OFSNet.h)

find_package(CURL REQUIRED)
find_package(zstd REQUIRED)

include_directories(${CURL_INCLUDE_DIR})

add_library(OFSNet ${NET_SOURCES})

target_link_libraries(OFSNet ${CURL_LIBRARIES} zstd)
