/*
 * Created by Terradice on 6/29/20 14:20:00
 */

#include "OFSPathDiscover.h"

#include <cstdlib>
#include <string>



OFSPathDiscover::OFSPathDiscover() {

#if __linux__
	 p_paths = {OFSUtil::exp_env("${HOME}/.steam/steam/")};
#else
	 p_paths = {"C:\\Program Files (x86)\\Steam"};
#endif

	for(auto &p : p_paths) {
		std::cout << p << std::endl;
		if(fs::exists(p)) {
			std::cout << "Found steam library: " << p << std::endl;

			p_steamPath = p;

			if(fs::exists(p / "steamapps/sourcemods")) {
				std::cout << "Path also contains sourcemods dir" << std::endl;
				p_sourcemodsPath = p / "steamapps/sourcemods";
			}

			if(fs::exists(
				   p / "steamapps/common/Source SDK Base 2013 Multiplayer")) {
				std::cout << "Path also contains Source SDK dir" << std::endl;
				p_sourcePath =
					p / "steamapps/common/Source SDK Base 2013 Multiplayer";
			}
		}
	}
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