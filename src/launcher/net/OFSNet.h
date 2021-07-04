//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSNET_H
#define OFLAUNCHER_STAINLESS_OFSNET_H

//#include "../lzma/OFLZMA.h"
#include "../db/OFSDatabaseElement.h"
#include <inttypes.h>
extern "C" {
#include "../../shared/minlzma/minlzma.h"
}
#include <stdint.h>
#include <cstring>
#include <string>
#include "OFFilesystem.h"
#include <cstdio>
#include <utility>
#include <iostream>
#include <memory>
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
//#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
//#include "cryptopp/md5.h"
#include "cryptopp/sha.h"
#include "cryptopp/rsa.h"



struct dfArgs {
	const std::string serverURL;
	const OFDbElement e;
	bool *done;

	dfArgs(const std::string &serverURL, const OFDbElement &e, bool *done) : serverURL(serverURL), e(e), done(done) {}
};

int downloadFile(void *ptr);
std::string downloadIntoString(const std::string &serverURL, const std::string &path);

class OFSNet {
public:
    explicit OFSNet(std::string serverURL, std::string &gameFolderName);
    OFSNet() =delete;
	std::string getServerURL();
	void setServerURL(std::string &URL);
	std::string getFolderName();
	void setFolderName(std::string name);
	void fetchDatabase();
	//void downloadFile(const std::string &path, const fs::path& to, const bool &decompress = false);


private:
	//static size_t memCallback(void *data, size_t size, size_t nmemb, void *userp);
    std::string p_serverURL;
    std::string p_dbFileName;
    std::string p_gameFolderName;
    fs::path p_cwd;


};

#endif // OFLAUNCHER_STAINLESS_OFSNET_H
