//
// Created by fenteale on 10/16/20.
//

#include "OFSSteam.h"

static std::vector<std::string> getLibraries(std::vector<std::string> &data)
{
	std::vector<std::string> libs;
	std::string ret = "";
	int libEntry = 1;
	while (true) {
		ret = "";
		for(auto &ln : data) {
			std::vector<std::string> parts;
			std::string partToAdd = "";
			for(char const &c : ln) {
				if(c == '\"') {
					parts.push_back(partToAdd);
					partToAdd = "";
				} else {
					partToAdd += c;
				}
			}
			if(parts.size() > 3)
				if(parts[1] == std::to_string(libEntry))
					ret = parts[3];
		}
		if(ret.empty())
			break;
		libs.push_back(ret + "/steamapps");
		libEntry++;
	}
	return libs;
}

OFSSteam::OFSSteam(std::string steamPath) : _steamDefaultDir(){
	_steamPath = _steamDefaultDir.getSteamPath();
	if(_steamPath.empty() || !steamPath.empty())
		_steamPath = steamPath;

	std::ifstream vdf(getSteamappsPath() / "libraryfolders.vdf");

	if(!vdf.is_open())
		throw std::runtime_error("Cannot open VDF file.");

	std::vector<std::string> vdfData;
	std::string line;

	while(getline(vdf, line))
		vdfData.push_back(line);

	vdf.close();

	_libPaths = getLibraries(vdfData);
	//_libPaths.insert(_libPaths.begin(), getSteamappsPath().string());
	_libPaths.push_back(getSteamappsPath().string());

	std::cout << "Meow" << std::endl;
	for(auto x: _libPaths)
		std::cout << x << std::endl;
}

fs::path OFSSteam::getSteamPath() {
	return _steamPath;
}

fs::path OFSSteam::getSourcemodsPath() {
	return _steamPath / "steamapps/sourcemods";
}

fs::path OFSSteam::getSteamappsPath() {
	return _steamPath / "steamapps";
}

OFSSteamApp *OFSSteam::getApp(int appID) {
	for(auto lib: _libPaths)
	{
		fs::path acfToCheck = lib;
		acfToCheck += "/appmanifest_" + std::to_string(appID) + ".acf";
		acfToCheck = acfToCheck.make_preferred();
		if(fs::exists(acfToCheck))
			return new OFSSteamApp(acfToCheck.string());
	}
	return nullptr;
}
