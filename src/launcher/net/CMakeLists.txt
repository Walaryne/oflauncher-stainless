SET(NET_SOURCES
        OFSNet.cpp
        OFSNet.h)

find_package(CURL REQUIRED)

find_path(ZSTD_INCLUDE_DIR zstd.h)
find_library(ZSTD_LIBRARY zstd)

include_directories(${CURL_INCLUDE_DIR} ../zstd/lib/)

add_library(OFSNet ${NET_SOURCES})

target_link_libraries(OFSNet ${CURL_LIBRARIES} libzstd_static)
