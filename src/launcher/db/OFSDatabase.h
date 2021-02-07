//
// Created by walaryne on 6/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSDATABASE_H
#define OFLAUNCHER_STAINLESS_OFSDATABASE_H

//From the SQLite manual:
#define ERRCHECK {if (err!=NULL) {std::cerr << err << std::endl; sqlite3_free(err);}}

#include "../net/OFSNet.h"
#include "../MD5/OFSVerifyIntegrity.h"
#include "SDL2/SDL.h"
#include <deque>
#include "OFFilesystem.h"
#include "../gui/OFSGuiActs.h"
#include <sqlite3.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <thread>

class OFSDatabase {
public:
	explicit OFSDatabase(OFSNet *net);
	OFSDatabase() =delete;
	void compareRevisions();
	int compareIntegrity();
	bool downloadSingleFile();
	bool downloadFiles(float &prog, int *act);
	int getQueueSize();
	void copyDb();

private:
	OFSNet *p_net;
	sqlite3 *p_dbFileLocal;
	sqlite3 *p_dbFileRemote;
	fs::path p_localDBPath;
	fs::path p_remoteDBPath;
	std::deque<std::string> p_downloadQueue;
	std::vector<std::string> p_remotePaths;
	std::vector<std::string> p_localPaths;
	static int databasePathConsumer(void *param, int argc, char **argv, char **column);
	static int databaseSingleResultConsumer(void *param, int argc, char **argv, char **column);
};

#endif // OFLAUNCHER_STAINLESS_OFSDATABASE_H
