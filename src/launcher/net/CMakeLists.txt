SET(NET_SOURCES
        OFSNet.cpp
        OFSNet.h
        OFSPubKey.h)

find_package(CURL REQUIRED)

find_path(ZSTD_INCLUDE_DIR zstd.h)
find_library(ZSTD_LIBRARY zstd)

if(CURL_FOUND)
    message("-- Found Curl")
else()
    message("-- CURL not found, terminating")
    return()
endif()

include_directories(${CURL_INCLUDE_DIRS} ../zstd/lib/)

add_library(OFSNet ${NET_SOURCES})

target_link_libraries(OFSNet ${CURL_LIBRARIES} libzstd_static)
