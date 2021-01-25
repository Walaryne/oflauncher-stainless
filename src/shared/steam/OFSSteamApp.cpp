//
// Created by fenteale on 10/19/20.
//

#include "OFSSteamApp.h"

static std::string parseValue(std::vector<std::string> &data, std::string valToFind)
{
	for(auto & ln : data)
	{
		std::vector<std::string> parts;
		std::string partToAdd = "";
		for(char const &c: ln){
			if(c == '\"')
			{
				parts.push_back(partToAdd);
				partToAdd = "";
			}
			else
			{
				partToAdd += c;
			}
		}
		if(parts.size() > 3)
			if(parts[1]==valToFind)
				return parts[3];
	}
	return "";
}

OFSSteamApp::OFSSteamApp(std::string acfPath) {
	_acfPath = acfPath;

	std::ifstream acf(acfPath);

	if(!acf.is_open())
		throw std::runtime_error("Cannot open ACF file.");

	std::vector<std::string> acfData;
	std::string line;

	while(getline(acf, line))
		acfData.push_back(line);

	acf.close();

	_appId = std::stoi(parseValue(acfData, "appid"));
	_appPath = _acfPath.parent_path() / "common" / parseValue(acfData, "installdir");
	_appName = parseValue(acfData, "name");
}

std::string OFSSteamApp::getName() {
	return _appName;
}

std::string OFSSteamApp::getInstallPath() {
	return _appPath.string();
}
