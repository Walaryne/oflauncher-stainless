//
// Created by walaryne on 6/14/20.
//

#include "OFSNet.h"
#include <fstream>
#include <utility>
#include <zstd.h>
#include "../hashlib2plus/hashlibpp.h"


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

	MD5 hash = MD5();
	HL_MD5_CTX* ctx = (HL_MD5_CTX*)std::malloc(16);
	hash.MD5Init(ctx);
	void* ptrs[2] = {ctx, file};


	std::cout << "SERVER PATH IS: " + (p_serverURL + path) << std::endl;
	curl_easy_setopt(p_curlh, CURLOPT_URL, (p_serverURL + path).c_str());
	curl_easy_setopt(p_curlh, CURLOPT_WRITEFUNCTION, DecompressStream);
	curl_easy_setopt(p_curlh, CURLOPT_WRITEDATA, (void *)ptrs);

	CURLcode retcode = curl_easy_perform(p_curlh);
	std::cout << "cURL return code: " << retcode << std::endl;

	// std::string checksum;
	// checksum.reserve(16);
	unsigned char checksum[16];
	hash.MD5Final(checksum, ctx);

	std::cout << "file checksum: " << checksum << std::endl;
}

//TODO: figure out how the callback works, add declarations, actually get it to work
size_t OFSNet::DecompressStream(char *ptr, size_t size, size_t nmemb, void* arg_ptr) {
	unsigned long long const outputSize = ZSTD_getDecompressedSize(ptr, size);
	if(outputSize == 0) {} // very bad
	unsigned char* outputBuffer = (unsigned char*)std::malloc(outputSize);
	ZSTD_DCtx* const zstd_ctx = ZSTD_createDCtx();
	ZSTD_inBuffer input = { ptr, nmemb, 0 };
	ZSTD_outBuffer output = { outputBuffer, outputSize, 0 };


	MD5 hash = MD5();
	HL_MD5_CTX* ctx = ((HL_MD5_CTX **)arg_ptr)[0];
	FILE *fout = ((FILE **)arg_ptr)[1];

	int ret = 0;
	while(input.pos < input.size) {
		ret |= ZSTD_decompressStream(zstd_ctx, &output, &input);
		ret |= std::fseek(fout, 0, SEEK_END);
		ret |= std::fwrite(outputBuffer, sizeof(unsigned char), outputSize/sizeof(unsigned char), fout);
		hash.MD5Update(ctx, outputBuffer, outputSize);
	}
	
	std::fflush(fout);
	std::fclose(fout);
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
