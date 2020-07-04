//
// Created by walaryne on 6/29/20.
//

#include "OFSFacade.h"

void *CreateInterface(char const *name, int *err) {
	static bool hasExec = false;
	static fs::path steamPath;

	if(!hasExec) {
		std::cout << "LOL IT WORKS FAM" << std::endl;

		OFSPathDiscover sPath;
		std::string steamPathStr = sPath.getSourcemodsPath();
		steamPathStr += "/open_fortress/bin";
		steamPath = steamPathStr;
		steamPath = steamPath.make_preferred();

		std::cout << "OF path: " << steamPath << std::endl;

		runLauncher(steamPath);

		hasExec = true;
	}

	return realClientInterface(name, err, steamPath);
}