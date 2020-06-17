//
// Created by walaryne on 6/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSDATABASE_H
#define OFLAUNCHER_STAINLESS_OFSDATABASE_H

#include "../net/OFSNet.h"
#include <deque>
#include <filesystem>
#include <sqlite3.h>

class OFSDatabase {
public:
	OFSDatabase(OFSNet *net);
	OFSDatabase() =delete;
	void updateGame();
	void verifyIntegrity();

private:
	OFSNet *p_net;
	sqlite3 *p_dbFileLocal;
	sqlite3 *p_dbFileRemote;
	std::deque<std::string> p_downloadQueue;
	void databaseQueryConsumer();
	void compareRevisions();
	void compareIntegrity();
	void downloadNewFiles();

};

#endif // OFLAUNCHER_STAINLESS_OFSDATABASE_H
