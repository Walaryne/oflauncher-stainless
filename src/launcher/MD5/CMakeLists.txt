SET(MD5_SOURCES
        OFSVerifyIntegrity.cpp
        OFSVerifyIntegrity.h)

add_library(OFSMD5 ${MD5_SOURCES})
target_link_libraries(OFSMD5 hashlib2plus)