//
// Created by fenteale on 10/19/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSSTEAMAPP_H
#define OFLAUNCHER_STAINLESS_OFSSTEAMAPP_H

#include <vector>
#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

enum steamAppState {
	NOT_READY1,
	NOT_READY2,
	NOT_READY3,
	NOT_READY4,
	READY_TO_PLAY
};

class OFSSteamApp {
private:
	fs::path _acfPath;
	int _appId;
	std::string _appName;
	fs::path _appPath;
public:
	OFSSteamApp(std::string acfPath);
	std::string getName();
	std::string getInstallPath();
	steamAppState getState();
};

#endif // OFLAUNCHER_STAINLESS_OFSSTEAMAPP_H
