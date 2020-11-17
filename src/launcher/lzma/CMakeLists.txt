SET(LZMA_SOURCES
        OFLZMA.cpp
        OFLZMA.h)

find_package(LibLZMA REQUIRED)

add_library(OFSLZMA ${LZMA_SOURCES})

target_link_libraries(OFSLZMA ${LIBLZMA_LIBRARIES})