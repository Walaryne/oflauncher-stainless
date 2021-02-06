//
// Created by walaryne on 6/14/20.
//

#include "OFSNet.h"
#include <fstream>
#include <utility>
#include <zstd.h>

OFSNet::OFSNet(std::string serverURL, std::string gameFolderName) {
	convertURL(serverURL);
	p_serverURL = std::move(serverURL);
	p_dbFileName = "ofmanifest.db";
	p_gameFolderName = std::move(gameFolderName);
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
	downloadFile("/" + p_dbFileName,
				 fs::path("launcher/remote").make_preferred() /
					 p_dbFileName);
	std::cout << "Database was fetched successfully!" << std::endl;
}

void OFSNet::downloadFile(const std::string &path, const fs::path& to, const bool &decompress) {
	fs::path dir = to;
	dir.remove_filename();
	std::cout << "Dir is: " + dir.string() << std::endl;

	if(!fs::exists(dir)) {
		fs::create_directories(dir);
	}

	FILE *file = std::fopen(to.string().c_str(), "wb");
	if(!file) {
		std::perror("FOPEN: ");
	}

	curl_mem_buf membuf{};

	std::cout << "SERVER PATH IS: " + (p_serverURL + path) << std::endl;
	curl_easy_setopt(p_curlh, CURLOPT_WRITEFUNCTION, OFSNet::memCallback);
	curl_easy_setopt(p_curlh, CURLOPT_WRITEDATA, &membuf);
	curl_easy_setopt(p_curlh, CURLOPT_URL, (p_serverURL + path).c_str());
	CURLcode retcode = curl_easy_perform(p_curlh);
	std::cout << "cURL return code: " << retcode << std::endl;

	//insert all the other friggin code here for unlzma and checksumming
	uint8_t* outputBuffer = nullptr;
	unsigned long long outputSize = 0;

	if (decompress && membuf.size != 0) {
		outputSize = ZSTD_getFrameContentSize(membuf.memfile,membuf.size);
		outputBuffer = (uint8_t*)std::malloc(outputSize);
		bool fail = ZSTD_isError(ZSTD_decompress(outputBuffer,outputSize,membuf.memfile, membuf.size));
		if(fail || !outputBuffer) {
			std::fflush(file);
			std::fclose(file);
			std::free(membuf.memfile);
			std::free(outputBuffer);

			throw std::runtime_error("Error decompressing file.");
		}
		else {
			std::fwrite(outputBuffer, sizeof(uint8_t), outputSize, file);
		}
	}
	else
		std::fwrite(membuf.memfile, sizeof(char), membuf.size, file);


	std::fflush(file);
	std::fclose(file);
	std::free(membuf.memfile);

}

void OFSNet::convertURL(std::string &URL) {
	if(URL.back() == '/') {
		URL.pop_back();
	}
}

std::string OFSNet::getFolderName() {
	return p_gameFolderName;
}

void OFSNet::setFolderName(std::string name) {
	p_gameFolderName = std::move(name);
}

size_t OFSNet::memCallback(void *data, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	auto *mem = static_cast<curl_mem_buf*> (userp);

	char *ptr =
		static_cast<char *>(realloc(mem->memfile, mem->size + realsize + 1));

	mem->memfile = ptr;

	std::memcpy(&(mem->memfile[mem->size]), data, realsize);
	mem->size += realsize;
	mem->memfile[mem->size] = 0;

	return realsize;
}
