//
// Created by walaryne on 6/15/20.
//

#include "OFSDatabase.h"

OFSDatabase::OFSDatabase(OFSNet *net) {
	p_net = net;
	p_dbFileRemote = nullptr;
	p_dbFileLocal = nullptr;

	fs::path localdb("launcher/local/ofmanifest.db");
	fs::path remotedb("launcher/remote/ofmanifest.db");

	if(fs::exists(localdb)) {
		//We already have a local db file, go ahead and load it
		sqlite3_open(localdb.make_preferred().string().c_str(), &p_dbFileLocal);
	}
	if(!fs::exists(remotedb)) {
		//Something failed miserably, we couldn't pull the new database from the server
		throw std::runtime_error("RemoteDB file was not found!");
	} else {
		int rc = sqlite3_open(remotedb.make_preferred().string().c_str(), &p_dbFileRemote);
		if(rc != SQLITE_OK) {
			throw std::runtime_error("SQLite database didn't open!");
		}
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
	char *err = nullptr;
	int rc =
		sqlite3_exec(p_dbFileRemote, "select path from files;",
					 OFSDatabase::databasePathConsumer, &p_remotePaths, &err);

	if(rc != SQLITE_OK) {
		ERRCHECK
		throw std::runtime_error("SQLite statement didn't execute!");
	}

	if(!p_dbFileLocal) {
		for(const auto &v : p_remotePaths) {
			p_downloadQueue.push_back(v);
		}
	} else {
		rc = sqlite3_exec(p_dbFileLocal, "select path from files;",
						  OFSDatabase::databasePathConsumer, &p_localPaths,
						  &err);

		if(rc != SQLITE_OK) {
			ERRCHECK
			throw std::runtime_error("SQLite statement didn't execute!");
		}

		for(const auto &v : p_remotePaths) {
			auto result = std::find(p_localPaths.begin(), p_localPaths.end(), v);

			//We found something!
			if(result != p_localPaths.end()) {

			}
		}
	}
}

void OFSDatabase::compareIntegrity() {
}

void OFSDatabase::downloadNewFiles() {
	for(const auto& s : p_downloadQueue) {
		p_net->downloadFile(s, (fs::path(p_net->getFolderName() + s)).make_preferred());
	}
}

int OFSDatabase::databasePathConsumer(void *param, int argc, char **argv, char **column) {
	auto strvec = static_cast<std::vector<std::string>*>(param);
	for(int i = 0; i < argc; ++i) {
		strvec->push_back(std::string(argv[i]));
	}
	return 0;
}

int OFSDatabase::databaseSingleResultConsumer(void *param, int argc, char **argv, char **column) {
	return 0;
}
