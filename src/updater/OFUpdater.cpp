//
// Created by Digit on 8/1/2020.
//

#include "OFUpdater.h"

#define OF_LAUNCHER_VERSION_ENDPOINT "https://puppy.surf/updater/version"
#define OF_LAUNCHER_CHECKSUM_ENDPOINT "https://puppy.surf/updater/checksum"
#define RENAME_BIN_NAME "OLD_LAUNCHER_BIN"

#if WIN32
#define OF_LAUNCHER_URL "https://puppy.surf/updater/oflauncher_stainless.exe"
#endif

#if __linux__
#define OF_LAUNCHER_URL "https://puppy.surf/updater/oflauncher_stainless"
#endif

OFUpdater::OFUpdater() {
	printf("Current Launcher Build #%i\n", OF_LAUNCHER_BUILD_NUMBER);
}

void OFUpdater::checkForUpdate() {
	checkVersionString();

	if(needsUpdating) {
		std::cout << "Launcher requires updating!" << std::endl;
		renameSelf();
		downloadNewVersion();
	} else {
        if(fs::exists(RENAME_BIN_NAME)) {
            while(!std::remove(RENAME_BIN_NAME)) {
                // PASS -- on linux it's perfectly ok to delete the bin while
                // it's loaded on windows, you can only rename things while
                // they're running so this is a dumb loop to wait for the old
                // launcher to close so we can delete it...
            }
        }
	}
}
void OFUpdater::checkVersionString() {
	auto curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, OF_LAUNCHER_VERSION_ENDPOINT);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
					 OFUpdater::versionDownloadCallback);
	curl_easy_setopt(
		curl, CURLOPT_TIMEOUT,
		3L); // Short timeout as to not delay startup time too much!
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

	auto res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	if(CURLE_OK != res) {
		std::cerr << "Issue fetching updater target version: " << res << '\n';
		return;
	}

	if (OF_LAUNCHER_BUILD_NUMBER < std::stoi(targetVersionString)) {
		needsUpdating = true;
	}
}

size_t OFUpdater::versionDownloadCallback(void *buffer, size_t size,
										 size_t nmemb, void *instance) {
	auto const updater = static_cast<OFUpdater *>(instance);
	size_t totalsize = size * nmemb;
	updater->targetVersionString.append(static_cast<char *>(buffer), totalsize);
	return totalsize;
}

void OFUpdater::renameSelf(bool reverse) {
	fs::path p = executablePath();
	std::string exeName = p.filename().u8string();

	// reverse is used to restore an old bin, in case we failed to DL a new one
	if(reverse) {
		std::rename(RENAME_BIN_NAME, exeName.c_str());
	} else {
		std::rename(exeName.c_str(), RENAME_BIN_NAME);
	}
}

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

	std::cout << "Finished!" << std::endl;

	fclose(fileHdl);

	// TODO Linux support and Checksum
	// We probably need to chmod it for linux here?
	// We also should use a checksum to ensure that the launcher is valid

	// Def a better way to do this -- just hacking it in to test
#if WIN32
	ShellExecute(nullptr, "open", executablePath().c_str(), "", nullptr,
				 SW_SHOW);
#endif

	// Exit!
	exit(0);
}

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