SET(HASH_SOURCES
        hashlibpp.h
        hl_exception.h
        hl_hashwrapper.h
        hl_md5.cpp
        hl_md5.h
        hl_md5wrapper.cpp
        hl_md5wrapper.h
        hl_types.h
        hl_wrapperfactory.cpp
        hl_wrapperfactory.h)

add_library(hashlib2plus ${HASH_SOURCES})