//
// Created by walaryne on 6/14/20.
//

#include "OFSNet.h"
#include <fstream>
#include <utility>
#include <zstd.h>
#include "md5.h"


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

	std::cout << "Writing to " << to.string().c_str() << std::endl;


	MD5 md5stream;
	void* ptrs[2] = {&md5stream, file};

	std::cout << "SERVER PATH IS: " + (p_serverURL + path) << std::endl;
	curl_easy_setopt(p_curlh, CURLOPT_URL, (p_serverURL + path).c_str());
	if(decompress)
		curl_easy_setopt(p_curlh, CURLOPT_WRITEFUNCTION, DecompressStream);
	else
		curl_easy_setopt(p_curlh, CURLOPT_WRITEFUNCTION, memCallback);

	curl_easy_setopt(p_curlh, CURLOPT_WRITEDATA, (void *)ptrs);

	CURLcode retcode = curl_easy_perform(p_curlh);
	FILE *fout = ((FILE **)ptrs)[1];
	std::fflush(fout);
	std::fclose(fout);

	std::cout << "cURL return code: " << retcode << std::endl;

	const char* checksum = md5stream.getHash().c_str();

	std::cout << "file checksum: " << checksum << std::endl;
}

size_t OFSNet::DecompressStream(char *ptr, size_t size, size_t nmemb, void* arg_ptr) {
	unsigned long long const outputSize = ZSTD_getDecompressedSize(ptr, size);
	if(outputSize == 0) {} // very bad
	unsigned char* outputBuffer = (unsigned char*)std::malloc(outputSize);
	ZSTD_DCtx* const zstd_ctx = ZSTD_createDCtx();
	ZSTD_inBuffer input = { ptr, nmemb, 0 };
	ZSTD_outBuffer output = { outputBuffer, outputSize, 0 };
	FILE *fout = ((FILE **)arg_ptr)[1];
	MD5 *md5s = ((MD5 **)arg_ptr)[0];
	int ret = 0;
	while(input.pos < input.size) {
		ret |= ZSTD_decompressStream(zstd_ctx, &output, &input);
		ret |= std::fseek(fout, 0, SEEK_END);
		ret |= std::fwrite(outputBuffer, sizeof(unsigned char), outputSize/sizeof(unsigned char), fout);
		md5s->add(outputBuffer, outputSize);
	}


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
	FILE *fout = ((FILE **)userp)[1];
	size_t written;
	written = std::fwrite(data, size, nmemb, fout);


	return written;

}
