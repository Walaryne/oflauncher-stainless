//
// Created by Digit on 8/1/2020.
//

#ifndef OFLAUNCHER_STAINLESS_OFUPDATER_H
#define OFLAUNCHER_STAINLESS_OFUPDATER_H

#include "../version.h"

#include <curl/curl.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

class OFUpdater {
public:
	OFUpdater();
	void checkForUpdate();

	std::string targetVersionString;

private:
	void fetchVersionString();
	static size_t versionCompareCallback(void *buffer, size_t size, size_t nmemb,
								  void *param);
	void splitVersionString();
	bool needsUpdating{};
	static void downloadNewVersion();
	static void renameSelf(bool reverse = false);
	static std::string executablePath();
};

#endif // OFLAUNCHER_STAINLESS_OFUPDATER_H