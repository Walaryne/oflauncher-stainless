/*
 * Created by Terradice on 6/29/20 14:20:00
 */

#ifndef OFLAUNCHER_STAINLESS_OFSPATH_H
#define OFLAUNCHER_STAINLESS_OFSPATH_H

#include "../util/OFSUtil.h"
#include <cstdlib>
#include "../../launcher/filesystem.h"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>



class OFSPathDiscover {
public:
	explicit OFSPathDiscover();
	std::string getSteamPath();
	std::string getSourcePath();
	std::string getSourcemodsPath();

private:
	void expandPaths();

	fs::path p_steamPath;
	fs::path p_sourcePath;
	fs::path p_sourcemodsPath;
	std::vector<fs::path> p_paths;
};

#endif // OFLAUNCHER_STAINLESS_OFSPATH_H
