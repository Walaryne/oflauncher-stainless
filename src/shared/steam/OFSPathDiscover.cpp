/*
 * Created by Terradice on 6/29/20 14:20:00
 */

#include "OFSPathDiscover.h"

#include <cstdlib>
#include <string>

#if WIN32
	#include <Windows.h>
	#include <winreg.h>
	#define WINDOWS_STEAM_REG_PATH "SOFTWARE\\Wow6432Node\\Valve\\Steam"
#endif

OFSPathDiscover::OFSPathDiscover() {
#if __linux__
	std::cout << "Platform is Linux" << std::endl;
	p_paths = {OFSUtil::exp_env("${HOME}/.steam/steam/")};
	for(auto &p : p_paths) {
		std::cout << p << std::endl;
		if(fs::exists(p)) {
			p_steamPath = p;
		}
	}
#endif

#if WIN32
	std::cout << "Platform is Windows" << std::endl;

	// Fallback common paths in case we cannot query the registry
	p_paths = {"C:\\Program Files (x86)\\Steam"};

	TCHAR regKeyValue[MAX_PATH];
	DWORD valueSize = sizeof(regKeyValue);
	LSTATUS queryResult =
		RegGetValueA(HKEY_LOCAL_MACHINE, WINDOWS_STEAM_REG_PATH, "InstallPath",
					 RRF_RT_REG_SZ, nullptr, &regKeyValue, &valueSize);
	if(queryResult == ERROR_SUCCESS) {
		std::cout << "Queried steam install path from system registry!" << std::endl;
		std::cout << regKeyValue << std::endl;
		p_steamPath = regKeyValue;
	} else {
		std::cout << "Failed to query steam install path from system registry, falling back to common paths!" << std::endl;
		for(auto &p : p_paths) {
			std::cout << p << std::endl;
			if(fs::exists(p)) {
				p_steamPath = p;
			}
		}
	}
#endif

	expandPaths();
}

std::string OFSPathDiscover::getSourcemodsPath() {
	return p_sourcemodsPath.string();
}

std::string OFSPathDiscover::getSteamPath() {
	return p_steamPath.string();
}

std::string OFSPathDiscover::getSourcePath() {
	return p_sourcePath.string();
}

void OFSPathDiscover::expandPaths() {
	if(fs::exists(p_steamPath)) {
		std::cout << "Found steam library: " << p_steamPath << std::endl;

		if(fs::exists(p_steamPath / "steamapps/sourcemods")) {
			std::cout << "Path also contains sourcemods dir" << std::endl;
			p_sourcemodsPath = p_steamPath / "steamapps/sourcemods";
		}

		if(fs::exists(p_steamPath /
					  "steamapps/common/Source SDK Base 2013 Multiplayer")) {
			std::cout << "Path also contains Source SDK dir" << std::endl;
			p_sourcePath = p_steamPath /
						   "steamapps/common/Source SDK Base 2013 Multiplayer";
		}
	} else {
		// TODO - probably throw a warning here??
		std::cout << "Found steam library -- BUT IT DOSEN'T EXIST: " << p_steamPath << std::endl;
	}
}