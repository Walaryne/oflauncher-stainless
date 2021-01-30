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
				 fs::path("launcher/remote").make_preferred() / p_dbFileName);
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
	//curl_easy_setopt(p_curlh, CURLOPT_WRITEFUNCTION, OFSNet::memCallback);
	//curl_easy_setopt(p_curlh, CURLOPT_WRITEDATA, &membuf);
	curl_easy_setopt(p_curlh, CURLOPT_URL, (p_serverURL + path).c_str());
	//CURLcode retcode = curl_easy_perform(p_curlh);
	//std::cout << "cURL return code: " << retcode << std::endl;
    curl_easy_setopt(p_curlh, CURLOPT_WRITEFUNCTION, DecompressStream);
    curl_easy_setopt(p_curlh, CURLOPT_WRITEDATA, (void *)&to);

}

//TODO: figure out how the callback works, add declarations, actually get it to work
size_t OFSNet::DecompressStream(char *ptr, size_t size, size_t nmemb, void* path){
		fs::path d_path = (char*)path;
		FILE *out = std::fopen(d_path.string().c_str(), "wb");
		ZSTD_DCtx* const zstd_context = ZSTD_createDCtx();
		size_t outputSize = ZSTD_DStreamOutSize();
		void* outputBuffer = std::malloc(outputSize);
		size_t toRead = nmemb;
		size_t ret;
		ZSTD_inBuffer input = { ptr, toRead, 0 };
		while (input.pos < input.size) {
			ZSTD_outBuffer output = { outputBuffer, outputSize, 0 };
			ret = ZSTD_decompressStream(zstd_context, &output , &input);
    }
	std::fwrite(outputBuffer, sizeof(uint8_t), outputSize, out);
	std::fflush(out);
	std::fclose(out);
	std::free(outputBuffer);
	return ret;
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
