//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSNET_H
#define OFLAUNCHER_STAINLESS_OFSNET_H

#include <curl/curl.h>
#include <string>
#include <filesystem>
#include <cstdio>
#include <utility>
#include <iostream>

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
	void downloadFile(const std::string &path, const fs::path &to);


private:
	static inline void convertURL(std::string &s);
    std::string p_serverURL;
    std::string p_dbFileName;
    std::string p_gameFolderName;
    fs::path p_cwd;
	CURL *p_curlh;
};

#endif // OFLAUNCHER_STAINLESS_OFSNET_H
