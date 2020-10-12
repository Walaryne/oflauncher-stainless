//
// Created by fenteale on 9/29/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFLZMA_H
#define OFLAUNCHER_STAINLESS_OFLZMA_H

#include <memory>
#include <vector>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <error.h>
#include <string.h>
//#include "SDK/CPP/7zip/Compress/LzmaDecoder.h"
#include "lzma.h"

class OFLZMA {
public:
	static uint8_t *decompress(unsigned char *inBuf, size_t inBufSize, size_t *outBufSize);
};

#endif // OFLAUNCHER_STAINLESS_OFLZMA_H
