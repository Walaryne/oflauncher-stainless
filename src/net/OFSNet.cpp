//
// Created by walaryne on 6/14/20.
//

#include "OFSNet.h"

OFSNet::OFSNet(std::string serverURL) {
	convertURL(serverURL);
	p_serverURL = std::move(serverURL);
	p_dbFileName = "ofsmanifest.db";
	p_curlh = curl_easy_init();
}

std::string OFSNet::getServerURL() {
	return p_serverURL;
}

void OFSNet::setServerURL(std::string URL) {
	convertURL(URL);
	p_serverURL = std::move(URL);
}

void OFSNet::fetchDatabase() {
	downloadFile("/" + p_dbFileName, fs::path("remote") / p_dbFileName);
}

void OFSNet::downloadFile(const std::string &path, const fs::path &to) {
	FILE *file = std::fopen(to.c_str(), "wb");
	curl_easy_setopt(p_curlh, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(p_curlh, CURLOPT_URL, (p_serverURL + path).c_str());
	curl_easy_perform(p_curlh);
}

void OFSNet::convertURL(std::string &URL) {
	if(URL.back() == '/') {
		URL.pop_back();
	}
}
