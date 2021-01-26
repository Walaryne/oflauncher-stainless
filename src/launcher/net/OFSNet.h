//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSNET_H
#define OFLAUNCHER_STAINLESS_OFSNET_H

#include <curl/curl.h>
//#include "../lzma/OFLZMA.h"
#include <inttypes.h>
extern "C" {
#include "../../shared/minlzma/minlzma.h"
}
#include <stdint.h>
#include <cstring>
#include <string>
#include <filesystem>
#include <cstdio>
#include <utility>
#include <iostream>
#include <memory>

namespace fs = std::filesystem;

class OFSNet {
public:
    explicit OFSNet(std::string serverURL, std::string gameFolderName);
    OFSNet() =delete;
	std::string getServerURL();
	void setServerURL(std::string URL);
	std::string getFolderName();
	void setFolderName(std::string name);
	void fetchDatabase();
	void downloadFile(const std::string &path, const fs::path& to, const bool &decompress = false);


private:
	static inline void convertURL(std::string &s);
	static size_t memCallback(void *data, size_t size, size_t nmemb, void *userp);
    std::string p_serverURL;
    std::string p_dbFileName;
    std::string p_gameFolderName;
    fs::path p_cwd;
	CURL *p_curlh;

	struct curl_mem_buf {
		char *memfile;
		size_t size;
	};
};

#endif // OFLAUNCHER_STAINLESS_OFSNET_H
