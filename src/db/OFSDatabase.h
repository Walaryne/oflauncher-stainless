//
// Created by walaryne on 6/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSDATABASE_H
#define OFLAUNCHER_STAINLESS_OFSDATABASE_H

//From the SQLite manual:
#define ERRCHECK {if (err!=NULL) {std::cerr << err << std::endl; sqlite3_free(err);}}

#include "../net/OFSNet.h"
#include <deque>
#include <filesystem>
#include <sqlite3.h>
#include <vector>
#include <cstring>
#include <iostream>

class OFSDatabase {
public:
	explicit OFSDatabase(OFSNet *net);
	OFSDatabase() =delete;
	void updateGame();
	void verifyIntegrity();

private:
	OFSNet *p_net;
	sqlite3 *p_dbFileLocal;
	sqlite3 *p_dbFileRemote;
	std::deque<std::string> p_downloadQueue;
	std::vector<std::string> p_remotePaths;
	std::vector<std::string> p_localPaths;
	static int databaseQueryConsumer(void *param, int argc, char **argv, char **column);
	void compareRevisions();
	void compareIntegrity();
	void downloadNewFiles();

};

#endif // OFLAUNCHER_STAINLESS_OFSDATABASE_H
