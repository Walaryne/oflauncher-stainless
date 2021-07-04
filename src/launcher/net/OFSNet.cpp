//
// Created by walaryne on 6/14/20.
//

#include "OFSNet.h"
#include <fstream>
#include <utility>
#include <zstd.h>
#include <curl/curl.h>
#include <glob.h>
#include "OFSPubKey.h"

struct curl_mem_buf {
	char *memfile;
	size_t size;
};

size_t memCallback(void *data, size_t size, size_t nmemb, void *userp) {
	// WHoled up
	size_t realsize = size * nmemb;
	auto *mem = static_cast<curl_mem_buf*> (userp);

	char *ptr =
		static_cast<char *>(realloc(mem->memfile, mem->size + realsize + 1));

	mem->memfile = ptr;

	std::memcpy(&(mem->memfile[mem->size]), data, realsize);
	mem->size += realsize;
	mem->memfile[mem->size] = 0;

	return realsize;

	/*
	size_t realsize = size * nmemb;
	auto *memstream = static_cast<std::iostream*> (userp);
	auto *ptr = static_cast<char *>(data);

	memstream->write(ptr, realsize);
	return realsize;
	 */
}


OFSNet::OFSNet(std::string serverURL, std::string &gameFolderName)
	: p_serverURL(std::move(serverURL)), p_dbFileName("ofmanifest.db"), p_gameFolderName(gameFolderName){
	curl_global_init(CURL_GLOBAL_ALL);
	if(p_serverURL.back() == '/') {
		p_serverURL.pop_back();
	}

}

std::string OFSNet::getServerURL() {
	return p_serverURL;
}

void OFSNet::setServerURL(std::string &URL) {
	p_serverURL = URL;
	if(p_serverURL.back() == '/') {
		p_serverURL.pop_back();
	}
}



static void downloadFileAndReturnArray(const std::string &serverURL, const std::string &path, const fs::path& to, const bool &decompress, uint8_t** dat, unsigned long long *dat_len) {
	CURL *curlh = curl_easy_init();



	fs::path origPath;
	if(to == "")
		origPath = (fs::current_path() / fs::path(path)).make_preferred();
	else
		origPath = to;

	fs::path dir = origPath;

	dir.remove_filename();
	//std::cout << "Dir is: " + dir.string() << std::endl;

	if(!fs::exists(dir)) {
		fs::create_directories(dir);
	}

	FILE *file = std::fopen(origPath.string().c_str(), "wb");
	if(!file) {
		std::perror("FOPEN: ");
	}

	curl_mem_buf membuf{};
	//std::streambuf membuf();

	//std::cout << "SERVER PATH IS: " + (serverURL + path) << std::endl;
	curl_easy_setopt(curlh, CURLOPT_WRITEFUNCTION, memCallback);
	curl_easy_setopt(curlh, CURLOPT_WRITEDATA, &membuf);
	curl_easy_setopt(curlh, CURLOPT_URL, (serverURL + path).c_str());
	CURLcode retcode = curl_easy_perform(curlh);
	curl_easy_cleanup(curlh);
	//std::cout << "cURL return code: " << retcode << std::endl;

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

			throw std::runtime_error("Error decompressing file (2).");
		}
		else {
			std::fwrite(outputBuffer, sizeof(uint8_t), outputSize, file);
			*dat = (uint8_t *) std::malloc(outputSize);
			std::memcpy(*dat, outputBuffer, outputSize);
			*dat_len = outputSize;
			std::free(outputBuffer);
		}
	}
	else {
		std::fwrite(membuf.memfile, sizeof(char), membuf.size, file);
		//*dat = (uint8_t *) std::malloc(membuf.size);
		//*dat_len = membuf.size;
	}

	std::fflush(file);
	std::fclose(file);
	std::free(membuf.memfile);

}

static void downloadFile(const std::string &serverURL, const std::string &path, const fs::path& to = "", const bool &decompress = false) {
	uint8_t* dat = nullptr;
	unsigned long long dat_len;
	downloadFileAndReturnArray(serverURL, path, to, decompress, &dat, &dat_len);
	if (dat)
		std::free(dat);
}

int downloadFile(void *ptr) {
	dfArgs *dfa = (dfArgs *)ptr;

	if (dfa->e.sig) {
		uint8_t* dat = nullptr;
		unsigned long long dat_len;
		downloadFileAndReturnArray(dfa->serverURL, dfa->e.path, "", true, &dat, &dat_len);

		std::string message = "RSA Signature";
		CryptoPP::RSA::PublicKey pub;
		CryptoPP::ByteQueue key_dat;
		key_dat.Put(decoded_dat, decoded_dat_len);
		try {
			pub.Load(key_dat);
		}
		catch (std::exception e) {
			std::cerr << "Error with loading the RSA key." << std::endl;
		}
		try {
			CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA384>::Verifier verifier(pub);

			CryptoPP::PK_MessageAccumulator* dat_ma = verifier.NewVerificationAccumulator();

			dat_ma -> Update(dat, dat_len);
			verifier.InputSignature(*dat_ma,(CryptoPP::byte *)dfa->e.sigData.c_str(), dfa->e.sigData.size() );
			if (!verifier.Verify(dat_ma))
				throw std::runtime_error("STUPID SIG FAILED!");
			//below here is just a ton of code I wrote and commented out and I have no idea if there are good ideas in here
			
			//CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(pub);
			//CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA384>::Verifier verifier(pub);
			//CryptoPP::SignatureVerificationFilter *vf = new CryptoPP::SignatureVerificationFilter(verifier);
			//vf->Put((CryptoPP::byte *)dfa->e.sigData.c_str(), dfa->e.sigData.size());
			//CryptoPP::PK_MessageAccumulator* dat_ma = verifier.NewVerificationAccumulator();
			//dat_ma -> Update(dat, dat_len);
			//verifier.InputSignature(*dat_ma,(CryptoPP::byte *)dfa->e.sigData.c_str(), dfa->e.sigData.size() );
			//CryptoPP::StringSource strsrc(dat, dat_len, );
			//if (!verifier.Verify(dat_ma))
			//	throw std::runtime_error("STUPID SIG FAILED!");
			//CryptoPP::StringSource ss2(
			//	dfa->e.sigData, true,
			//	new CryptoPP::SignatureVerificationFilter(
			//		verifier, NULL,
			//		CryptoPP::SignatureVerificationFilter::THROW_EXCEPTION));
		}
		catch (std::runtime_error e) {
			std::cerr << e.what() << std::endl;
			throw;
			//std::cerr << e.GetErrorType() << std::endl;
		}
		std::cout << "MEOW MEOW MEOW MEOW MEOW!!!!! " << dfa->e.path << std::endl;
		if (dat)
			std::free(dat);
	}
	else {
		downloadFile(dfa->serverURL, dfa->e.path, "", true);
	}

	*(dfa->done) = true;
	return 0;
}

std::string downloadIntoString(const std::string &serverURL, const std::string &path) {
	CURL *curlh = curl_easy_init();

	curl_mem_buf membuf{};

	//std::cout << "SERVER PATH IS: " + (serverURL + path) << std::endl;
	curl_easy_setopt(curlh, CURLOPT_WRITEFUNCTION, memCallback);
	curl_easy_setopt(curlh, CURLOPT_WRITEDATA, &membuf);
	curl_easy_setopt(curlh, CURLOPT_URL, (serverURL + path).c_str());
	CURLcode retcode = curl_easy_perform(curlh);
	curl_easy_cleanup(curlh);
	//std::cout << "cURL return code: " << retcode << std::endl;

	if(retcode != CURLE_OK)
		throw std::runtime_error("Error downloading file.");

	std::string ret(membuf.memfile, membuf.size);

	return ret;
}

void OFSNet::fetchDatabase() {
	downloadFile(p_serverURL, "/" + p_dbFileName,
				 fs::path("launcher/remote").make_preferred() /
				 p_dbFileName);
	std::cout << "Database was fetched successfully!" << std::endl;
}

std::string OFSNet::getFolderName() {
	return p_gameFolderName;
}

void OFSNet::setFolderName(std::string name) {
	p_gameFolderName = std::move(name);
}


