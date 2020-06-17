//
// Created by walaryne on 6/15/20.
//

#include "OFSDatabase.h"

OFSDatabase::OFSDatabase(OFSNet *net) {
	p_net = net;

	fs::path localdb("local/ofmanifest.db");
	fs::path remotedb("remote/ofmanifest.db");
	if(fs::exists(localdb)) {
		//We already have a local db file, go ahead and load it
		sqlite3_open(("file:" + localdb.string()).c_str(), &p_dbFileLocal);
	}
	if(!fs::exists(remotedb)) {
		//Something failed miserably, we couldn't pull the new database from the server
		throw std::runtime_error("RemoteDB file was not found!");
	} else {
		sqlite3_open(("file:" + remotedb.string()).c_str(), &p_dbFileRemote);
	}
}

void OFSDatabase::updateGame() {
	compareRevisions();
	downloadNewFiles();
}

void OFSDatabase::verifyIntegrity() {
	compareIntegrity();
	downloadNewFiles();
}

void OFSDatabase::compareRevisions() {
	//sqlite3_exec(p_dbFileRemote, "select * from table files;", )
}

void OFSDatabase::compareIntegrity() {
}

void OFSDatabase::downloadNewFiles() {
}

void OFSDatabase::databaseQueryConsumer() {
}
