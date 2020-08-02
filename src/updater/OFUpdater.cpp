//
// Created by Digit on 8/1/2020.
//

#include "OFUpdater.h"

#define OF_LAUNCHER_VERSION_ENDPOINT "https://puppy.surf/updater/version"
#define OF_LAUNCHER_CHECKSUM_ENDPOINT "https://puppy.surf/updater/checksum"
#define OLD_LAUNCHER_BIN_NAME "OLD_OPEN_FORTRESS_LAUNCHER_BIN"

#if WIN32
#define OF_LAUNCHER_URL "https://puppy.surf/updater/oflauncher_stainless.exe"
#endif

#if __linux__
#define OF_LAUNCHER_URL "https://puppy.surf/updater/oflauncher_stainless"
#endif

OFUpdater::OFUpdater() {
	std::cout << "Current Launcher Build #" <<  OF_LAUNCHER_BUILD_NUMBER << std::endl;
}

/**
 * Kicks up update pipeline
 * Will clean up files that match the name OLD_LAUNCHER_BIN_NAME in the
 * current working directory.
 */
void OFUpdater::checkForUpdate() {
	checkVersionString();
	fetchChecksum();

	// Ensure the working directory is the one that contains the launcher bin
	fs::path workingDir = executablePath();
	fs::current_path(workingDir.remove_filename());

	if(needsUpdating) {
		std::cout << "Launcher requires updating!" << std::endl;
		renameSelf();
		downloadNewVersion();
        validateChecksum();
        //rebootLauncher();
    } else {
        if(fs::exists(OLD_LAUNCHER_BIN_NAME)) {
			std::cout << "Found old launcher bin, removing it!" << std::endl;
            while(!std::remove(OLD_LAUNCHER_BIN_NAME)) {
                // PASS -- on linux it's perfectly ok to delete the bin while
                // it's loaded on windows, you can only rename things while
                // they're running so this is a dumb loop to wait for the old
                // launcher to close so we can delete it...
            }
        }
	}
}

/**
 * Fetches launcher build number from server
 */
void OFUpdater::checkVersionString() {
	bool result = fetchString(OF_LAUNCHER_VERSION_ENDPOINT, targetVersionString);
	if (!result) {
		std::cout << "Failed to fetch version string from server!";
        std::cout << "Skipping launcher update check.";
        needsUpdating = false;
		return;
	}

    int targetBuildNumber = std::stoi(targetVersionString);
	std::cout << "Server reports Build #" << targetBuildNumber << std::endl;

	if (OF_LAUNCHER_BUILD_NUMBER < targetBuildNumber) {
		needsUpdating = true;
	}
}

/**
 * Fetches launcher checksum from server
 */
void OFUpdater::fetchChecksum() {
    bool result = fetchString(OF_LAUNCHER_CHECKSUM_ENDPOINT, targetVersionChecksum);
    if (!result) {
        std::cout << "Failed to fetch checksum string from server!";
        std::cout << "Skipping launcher update check.";
		needsUpdating = false;
        return;
    }

    std::cout << "Server reports checksum: " << targetVersionChecksum << std::endl;
}

/**
 * Fetches string data from a URL and loads it into a std::string of choice
 * @param URL - URL of string content to fetch
 * @param outData - Reference to string variable to store results in
 */
bool OFUpdater::fetchString(std::string URL, std::string &outData) {
    auto curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outData);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
		+[](void *buffer, size_t size, size_t nmemb, void *userp) -> size_t {
          size_t totalSize = size * nmemb;
          auto const value = static_cast<std::string*>(userp);
          value->append(static_cast<char *>(buffer), totalSize);
		  return totalSize;
	});

    auto res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

	return res == CURLE_OK;
}

/**
 * Renames THIS bin in prep for it being replaced by a new launcher bin
 * @param restore - instead of rename this bin's name -> OLD_LAUNCHER_BIN_NAME
 * we will rename OLD_LAUNCHER_BIN_NAME -> this bin's original name
 * useful for when checksums fail to pass, or DL fails
 */
void OFUpdater::renameSelf(bool restore) {
	fs::path p = executablePath();
	std::string exeName = p.filename().u8string();

	// restore is used to restore the old bin, in case we failed to DL a new one
	if(restore) {
		std::cout << "Restoring old launcher bin" << std::endl;
		std::rename(OLD_LAUNCHER_BIN_NAME, exeName.c_str());
	} else {
        std::cout << "Moving current launcher" << std::endl;
		std::rename(exeName.c_str(), OLD_LAUNCHER_BIN_NAME);
	}
}

/**
 * Downloads a new version of the launcher bin to this bin's original name
 */
void OFUpdater::downloadNewVersion() {
	std::cout << "Downloading new launcher from server..." << std::endl;

	fs::path p = executablePath();
	std::string exeName = p.filename().u8string();

	auto fileHdl = fopen(exeName.c_str(), "wb");

	auto curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, OF_LAUNCHER_URL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fileHdl);

	auto res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	if(CURLE_OK != res) {
		std::cerr << "Issue fetching updater target version: " << res << '\n';
		renameSelf(true); // Return the old bin back to the original name
		return;
	}

	std::cout << "Downloaded new launcher bin." << std::endl;

	fclose(fileHdl);
}

void OFUpdater::rebootLauncher() {
#if __linux__
    chmod(executablePath().c_str(), S_IRWXU);
#endif

#if WIN32
    ShellExecute(nullptr, "open", executablePath().c_str(), "", nullptr, SW_SHOW);
#endif

    // Exit this launcher instance
    exit(0);
}

/**
 * @return this bin's current full path
 */
std::string OFUpdater::executablePath() {
#if defined(PLATFORM_POSIX) || defined(__linux__)
	// TODO -- Haven't tested this yet!!!
	std::string sp;
	std::ifstream("/proc/self/comm") >> sp;
	return sp;

#elif defined(_WIN32)
	char fileNameBuffer[MAX_PATH];
	GetModuleFileNameA(nullptr, fileNameBuffer, MAX_PATH);
	return fileNameBuffer;
#endif
}
void OFUpdater::validateChecksum() {
    fs::path p = executablePath();
    std::string exeName = p.filename().u8string();

    std::ifstream fileStream(exeName.c_str(), std::ios::in | std::ios::binary);


    MD5_CTX ctx;
    MD5_Init(&ctx);

    char tempBuffer[512];
    while (fileStream.read(tempBuffer, sizeof(tempBuffer)) || fileStream.gcount()) {
        MD5_Update(&ctx, tempBuffer, fileStream.gcount());
    }

    unsigned char digest[16];
    MD5_Final(digest, &ctx);

	std::string md5String;
    char md5string[33];
    for(int i = 0; i < 16; ++i)
        sprintf(&md5string[i*2], "%02x", (unsigned int)digest[i]);

	std::cout << "MD5 Checksum of launcher bin: " << md5string << std::endl;
}
