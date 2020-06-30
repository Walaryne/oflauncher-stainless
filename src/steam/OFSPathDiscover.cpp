/*
 * Created by Terradice on 6/29/20 14:20:00
 */

#include "OFSPathDiscover.h"

#include <cstdlib>
#include <string>

#if __linux__
const std::vector<fs::path> paths{exp_env("${HOME}/.steam/steam/")};
#else
const std::vector<fs::path> paths{"C:\\Program Files (x86)\\Steam"};
#endif

OFSPathDiscover::OFSPathDiscover() {

	for(auto &p : paths) {
		std::cout << p << std::endl;
		if(fs::exists(p)) {
			std::cout << "Found steam library: " << p << std::endl;

			steamPath = p;

			if(fs::exists(p / "steamapps/sourcemods")) {
				std::cout << "Path also contains sourcemods dir" << std::endl;
				sourcemodsPath = p / "steamapps/sourcemods";
			}

			if(fs::exists(
				   p / "steamapps/common/Source SDK Base 2013 Multiplayer")) {
				std::cout << "Path also contains Source SDK dir" << std::endl;
				sourcePath =
					p / "steamapps/common/Source SDK Base 2013 Multiplayer";
			}
		}
	}
}

std::string OFSPathDiscover::getSourcemodsPath() {
	return sourcemodsPath;
}