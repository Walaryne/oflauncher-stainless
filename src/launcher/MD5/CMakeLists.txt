SET(MD5_SOURCES
        OFSVerifyIntegrity.cpp
        OFSVerifyIntegrity.h)

find_path(CryptoPP_INCLUDE_DIR cryptopp)
find_library(CryptoPP_LIBRARIES cryptopp-shared)

add_library(OFSMD5 ${MD5_SOURCES})
#target_link_libraries(OFSMD5 hashlib2plus)

target_link_libraries(OFSMD5 ${CryptoPP_LIBRARIES})
#for static I think all you gotta do is link crypto-static instead