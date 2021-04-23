SET(MD5_SOURCES
        OFSVerifyIntegrity.cpp
        OFSVerifyIntegrity.h)

#find_package(cryptopp-cmake)

add_library(OFSMD5 ${MD5_SOURCES})
#target_link_libraries(OFSMD5 hashlib2plus)

target_link_libraries(OFSMD5 cryptopp-shared)
#for static I think all you gotta do is link crypto-static instead