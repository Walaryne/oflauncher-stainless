//
// Created by fenteale on 11/17/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSLAUNCHOPT_H
#define OFLAUNCHER_STAINLESS_OFSLAUNCHOPT_H

#include <string>
#include <experimental/filesystem>
#include <vector>
#include <iostream>
#include <fstream>

namespace fs=std::experimental::filesystem;

class OFSSteamUser {
public:
	OFSSteamUser(std::string name, std::string avPic):name(name),avPic(avPic) {};
	OFSSteamUser(std::string name, fs::path vdfPath):name(name),vdfPath(vdfPath) {};
	std::string name;
	std::string avPic;
	fs::path vdfPath;
};

class OFSUserSettings {
private:
	std::vector<OFSSteamUser> _users;
public:
	OFSUserSettings(fs::path steamPath);
	void setLaunchOpt(OFSSteamUser user, std::string launchOpt);
	std::vector<OFSSteamUser> getUsers() {return _users;}
};

#endif // OFLAUNCHER_STAINLESS_OFSLAUNCHOPT_H
