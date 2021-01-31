SET(NET_SOURCES
        OFSNet.cpp
        OFSNet.h)

find_package(CURL REQUIRED)

find_path(ZSTD_INCLUDE_DIR zstd.h)
find_library(ZSTD_LIBRARY zstd)

include_directories(${CURL_INCLUDE_DIR} ${ZSTD_INCLUDE_DIR})

add_library(OFSNet ${NET_SOURCES})
if(${zstd_FOUND})
	target_link_libraries(OFSNet PUBLIC zstd ${CURL_LIBRARIES})
elseif(${libzstd_FOUND})
	target_link_libraries(OFSNet PUBLIC libzstd ${CURL_LIBRARIES})
else()
	message("Zstd not found!")
endif()
