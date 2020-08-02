//
// Created by Digit on 8/1/2020.
//

#ifndef OFLAUNCHER_STAINLESS_OFUPDATER_H
#define OFLAUNCHER_STAINLESS_OFUPDATER_H

#include "../version.h"
#include "../shared/util/md5.h"

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
	std::string targetVersionChecksum;

private:
    bool checkVersionString();
    bool fetchChecksum();
    bool validateChecksum() const;
    static bool downloadNewVersion();
    static bool renameSelf(bool restore = false);

	static bool fetchString(const std::string& URL, std::string &outData);
    static std::string executablePath();

    bool needsUpdating = false;
	static void rebootLauncher();
};

#endif // OFLAUNCHER_STAINLESS_OFUPDATER_H
