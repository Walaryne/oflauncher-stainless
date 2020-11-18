//
// Created by fenteale on 11/17/20.
//

#include "OFSLaunchOpt.h"

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

OFSUserSettings::OFSUserSettings(fs::path steamPath) {
	std::vector<fs::path> userConfigs;

	fs::path userDir = steamPath / "userdata";
	for(auto &entry : fs::directory_iterator(userDir)) {
		fs::path vdfPath = entry.path() / "config" / "localconfig.vdf";
		if(fs::exists(vdfPath))
			userConfigs.push_back(vdfPath);
	}

	for(auto &e : userConfigs) {
		std::ifstream vdf(e);

		if(!vdf.is_open())
			throw std::runtime_error("Cannot open VDF file.");

		std::vector<std::string> vdfData;
		std::string line;
		while(getline(vdf, line))
			vdfData.push_back(line);
		_users.push_back(OFSSteamUser(parseValue(vdfData, "PersonaName"), e));

		vdf.close();
	}
	std::cout << "Detected steam users:" << std::endl;
	for(auto &u : _users)
		std::cout << u.name << std::endl;


}

void OFSUserSettings::setLaunchOpt(OFSSteamUser user, std::string launchOpt) {
	std::string toFind = "243750_2718784665";

	std::ifstream vdf(user.vdfPath);

	std::vector<std::string> vdfData;
	std::string line;

	while(getline(vdf, line))
		vdfData.push_back(line);

	int linenum = 0;
	int foundEntry=0;
	for(auto &l : vdfData) {
		if(l.find(toFind)!=std::string::npos) {
			foundEntry = linenum;
			break;
		}
		linenum++;
	}
	vdf.close();
	if(foundEntry) {
		std::ofstream vdfOut(user.vdfPath, std::ios::out | std::ios::trunc);

		linenum = 0;
		for(auto &l : vdfData) {
			if(linenum == foundEntry+2)
				vdfOut << "\t\t\t\t\t\t\"LaunchOptions\"\t\t\"" << launchOpt << "\"" << std::endl;
			else
				vdfOut << l << std::endl;
			linenum++;
		}
		vdfOut.close();
	}
	else {
		int linenum = 0;
		int foundEntry=0;
		for(auto &l : vdfData) {
			if(l.find("\"Steam\"")!=std::string::npos) {
				foundEntry = linenum;
				break;
			}
			linenum++;
		}
		if(!foundEntry)
			return;
		foundEntry+=4;

		std::ofstream vdfOut(user.vdfPath, std::ios::out | std::ios::trunc);

		linenum = 0;
		for(auto &l : vdfData) {
			if(linenum == foundEntry) {
				vdfOut << "\t\t\t\t\t\"" << toFind << "\"" << std::endl;
				vdfOut << "\t\t\t\t\t{" << std::endl;
				vdfOut << "\t\t\t\t\t\t\"LaunchOptions\"\t\t\"" << launchOpt
					   << "\"" << std::endl;
				vdfOut << "\t\t\t\t\t}" << std::endl;
			}

			vdfOut << l << std::endl;
			linenum++;
		}
		vdfOut.close();
	}
}