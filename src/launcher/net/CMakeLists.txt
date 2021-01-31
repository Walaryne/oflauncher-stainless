SET(NET_SOURCES
        OFSNet.cpp
        OFSNet.h)

find_package(CURL REQUIRED)
find_package(libzstd QUIET)
find_package(zstd QUIET)

include_directories(${CURL_INCLUDE_DIR})

add_library(OFSNet ${NET_SOURCES})
if(${zstd_FOUND})
	target_link_libraries(OFSNet PUBLIC zstd ${CURL_LIBRARIES})
elseif(${libzstd_FOUND})
	target_link_libraries(OFSNet PUBLIC libzstd ${CURL_LIBRARIES})
else()
	message("Zstd not found!")
endif()
