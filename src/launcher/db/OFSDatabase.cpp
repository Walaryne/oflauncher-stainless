//
// Created by walaryne on 6/15/20.
//

#include "OFSDatabase.h"

OFSDatabase::OFSDatabase(OFSNet *net) {
	p_net = net;
	p_dbFileRemote = nullptr;
	p_dbFileLocal = nullptr;

	p_localDBPath = "launcher/local/ofmanifest.db";
	p_remoteDBPath = "launcher/remote/ofmanifest.db";

	if(fs::exists(p_localDBPath)) {
		//We already have a local db file, go ahead and load it
		sqlite3_open(p_localDBPath.make_preferred().string().c_str(), &p_dbFileLocal);
	}
	if(!fs::exists(p_remoteDBPath)) {
		//Something failed miserably, we couldn't pull the new database from the server
		throw std::runtime_error("RemoteDB file was not found!");
	} else {
		int rc = sqlite3_open(p_remoteDBPath.make_preferred().string().c_str(), &p_dbFileRemote);
		if(rc != SQLITE_OK) {
			throw std::runtime_error("SQLite database didn't open!");
		}
	}
}

void OFSDatabase::compareRevisions() {
	char *err = nullptr;
	int rc = sqlite3_exec(p_dbFileRemote, "select path from files;",
					 OFSDatabase::databasePathConsumer, &p_remotePaths, &err);

	if(rc != SQLITE_OK) {
		ERRCHECK
		throw std::runtime_error("SQLite statement didn't execute!");
	}

	p_downloadQueue.clear();

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
				std::string remoteStmtRes;
				std::string localStmtRes;
				std::string stmt = (std::string("select revision from files where path='") + v + "';");

				rc = sqlite3_exec(p_dbFileRemote, stmt.c_str(),
								  OFSDatabase::databaseSingleResultConsumer, &remoteStmtRes,
								  &err);

				rc = sqlite3_exec(p_dbFileLocal, stmt.c_str(),
								  OFSDatabase::databaseSingleResultConsumer, &localStmtRes,
								  &err);

				if(rc != SQLITE_OK) {
					ERRCHECK
					throw std::runtime_error("SQLite statement didn't execute!");
				}

				std::cout << "Filename: " << v << std::endl;
				std::cout << "Remote: " << remoteStmtRes << std::endl;
				std::cout << "Local: " << localStmtRes << std::endl;

				if(localStmtRes != remoteStmtRes) {
					std::cout << "Revisions don't match, adding to download queue" << std::endl;
					p_downloadQueue.push_back(v);
				}

			} else {
				p_downloadQueue.push_back(v);
			}
		}
	}
}

int OFSDatabase::compareIntegrity() {
	if(!p_dbFileLocal)
		return -1;
		//throw std::runtime_error("Please generate local DB before trying to compare integrity!!");
	p_net->fetchDatabase();
	int rc = sqlite3_open(p_remoteDBPath.make_preferred().string().c_str(), &p_dbFileRemote);
	if(rc != SQLITE_OK) {
		throw std::runtime_error("SQLite database didn't open!");
	}

	int ret = 0;
	std::vector<std::basic_string<char>> remoteCS;
	char *err = nullptr;
	std::vector<std::basic_string<char>> localFiles;
	rc = sqlite3_exec(p_dbFileLocal, "select path from files;",
						  OFSDatabase::databasePathConsumer, &localFiles, &err);

	if(rc != SQLITE_OK) {
		ERRCHECK
		throw std::runtime_error("SQLite statement didn't execute!");
	}

	for(auto &lf : localFiles)
	{
		std::basic_string<char> cs = "";
		std::string cmd = "select checksum from files where path=\""+lf+"\";";
		rc = sqlite3_exec(p_dbFileLocal, cmd.c_str(),
						  OFSDatabase::databaseSingleResultConsumer, &cs, &err);

		if(rc != SQLITE_OK) {
			ERRCHECK
			throw std::runtime_error("SQLite statement didn't execute!");
		}
		if(!verifyIntegrity(fs::path(lf), cs)) {
			std::cout << lf << " IS BAD!!!!" << std::endl;
			cmd = "update files set revision=-1 where path=\""+lf+"\";";
			rc = sqlite3_exec(p_dbFileLocal, cmd.c_str(),
							  nullptr, nullptr, &err);
			if(rc != SQLITE_OK) {
				ERRCHECK
				throw std::runtime_error("SQLite statement didn't execute!");
			}
			ret++;
		}
	}

	return ret;
}

bool OFSDatabase::downloadSingleFile() {
	if(!p_downloadQueue.empty()) {
		std::string file = p_downloadQueue.front();
		std::cout << "Downloading file: " << file << std::endl;
		//p_net->downloadFile("/" + file, "", true);
		p_downloadQueue.pop_front();
		return false;
	} else {
		return true;
	}
}

static int tcounter = 0;

struct downloadThread {
	SDL_Thread *t;
	bool *done;
	dfArgs *a;

	downloadThread(const std::string &serverURL, const std::string path) {
		done = new bool;
		*done = false;
		a = new dfArgs(serverURL, path, done);
		std::string tn = "df";
		tn.append(std::to_string(tcounter));
		tcounter++;

		t = SDL_CreateThread(downloadFile, tn.c_str(), (void *)a);
		SDL_DetachThread(t);
	}
};

bool OFSDatabase::downloadFiles(float &prog, int *act) {
	std::string serverURL = p_net->getServerURL() + "/";

	int numThreads = 0;
	int numThreadsMax = SDL_GetCPUCount() - 1;
	std::cout << "Spawning maximum of " << numThreadsMax << " threads." << std::endl;


	int totalFiles = p_downloadQueue.size();
	int queue = totalFiles;

	std::vector<downloadThread> threads;

	while(!p_downloadQueue.empty() && *act != BUT_CLICKED_CANCEL) {
		while(numThreads < numThreadsMax && !p_downloadQueue.empty() ) {
			std::cout << "Creating thread to download " << p_downloadQueue.front() << std::endl;
			threads.push_back(std::move(downloadThread(serverURL, p_downloadQueue.front())));
			p_downloadQueue.pop_front();
			queue--;
			numThreads++;
		}

		for(auto &i : threads) {
			if(*(i.done)) {
				std::cout << "Thread finished." << std::endl;
				numThreads--;
				*(i.done) = false;
			}
		}
		prog = ((float)totalFiles - (float)queue) / (float)totalFiles;
		SDL_Delay(1);

	}
	return true;
}

int OFSDatabase::databasePathConsumer(void *param, int argc, char **argv, char **column) {
	auto strvec = static_cast<std::vector<std::string>*>(param);
	for(int i = 0; i < argc; ++i) {
		strvec->push_back(std::string(argv[i]));
	}
	return 0;
}

int OFSDatabase::databaseSingleResultConsumer(void *param, int argc, char **argv, char **column) {
	auto retstring = static_cast<std::string *>(param);
	*retstring = std::string(argv[0]);
	return 0;
}

void OFSDatabase::copyDb() {
	if(fs::exists(p_localDBPath)) {
		fs::remove(p_localDBPath);
	}

	fs::copy(p_remoteDBPath, p_localDBPath);
	sqlite3_open(p_localDBPath.make_preferred().string().c_str(), &p_dbFileLocal);
}

int OFSDatabase::getQueueSize() {
	return p_downloadQueue.size();
}
