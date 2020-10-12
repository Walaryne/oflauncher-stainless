//
// Created by fenteale on 9/29/20.
//

#include "OFLZMA.h"

//lotsa spaghetti copied from https://github.com/kobolabs/liblzma/blob/master/src/xzdec/xzdec.c

uint8_t * OFLZMA::decompress(uint8_t *inBuf, size_t inBufSize, size_t *outBufSize) {
	uint8_t *outBuf = nullptr;
	*outBufSize = 0;

	lzma_stream strm = LZMA_STREAM_INIT;

	lzma_ret ret;

	ret = lzma_stream_decoder(&strm, UINT64_MAX, LZMA_CONCATENATED);

	// The only reasonable error here is LZMA_MEM_ERROR.
	if(ret != LZMA_OK) {
		lzma_end(&strm);
		return nullptr;
	}

	uint8_t buf[BUFSIZ];


	strm.avail_in = 0;

	//strm.next_out = outBuf;
	strm.next_out = buf;
	strm.avail_out = BUFSIZ;

	lzma_action action = LZMA_RUN;

	while(true) {
		if(strm.avail_in == 0) {
			strm.next_in = inBuf;
			strm.avail_in = inBufSize;
		}

		ret = lzma_code(&strm, LZMA_FINISH);

		// Write and check write error before checking decoder error.
		// This way as much data as possible gets written to output
		// even if decoder detected an error.
		if(strm.avail_out == 0 || ret != LZMA_OK) {
			const size_t write_size = BUFSIZ - strm.avail_out;


			uint8_t *tmpBuf = nullptr;
			if(outBuf)
			{
				tmpBuf = (uint8_t*)malloc(*outBufSize + write_size);
				memcpy(tmpBuf, outBuf, *outBufSize);
				memcpy(tmpBuf+ *outBufSize, buf, write_size);
				free(outBuf);
				outBuf = tmpBuf;
			}
			else {
				outBuf = (uint8_t *)malloc(write_size);
				memcpy(outBuf, buf, write_size);
			}

			*outBufSize += write_size;

			strm.next_out = buf;
			strm.avail_out = BUFSIZ;
		}

		if(ret != LZMA_OK) {
			if(ret == LZMA_STREAM_END) {

				lzma_end(&strm);
				return outBuf;
			}

			const char *msg;
			switch(ret) {
			case LZMA_MEM_ERROR:
				msg = strerror(ENOMEM);
				break;

			case LZMA_FORMAT_ERROR:
				msg = "File format not recognized";
				break;

			case LZMA_OPTIONS_ERROR:
				// FIXME: Better message?
				msg = "Unsupported compression options";
				break;

			case LZMA_DATA_ERROR:
				msg = "File is corrupt";
				break;

			case LZMA_BUF_ERROR:
				msg = "Unexpected end of input";
				break;

			default:
				msg = "Internal error (bug)";
				break;
			}

			std::cerr << msg << std::endl;
			lzma_end(&strm);
			return nullptr;
		}
	}
}