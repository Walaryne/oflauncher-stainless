//
// Created by fenteale on 11/15/20.
//

#include "OFSVerifyIntegrity.h"


//static hashwrapper *md5 = new md5wrapper();


bool verifyIntegrity(fs::path fToCheck, std::string md5db) {
	//CryptoPP::Weak1::MD5 hash;

	std::string md5ret = "";
	std::string digest;
	//std::ifstream fileToHash(fToCheck.make_preferred().string(), std::ios::binary | std::ios::ate);
	//CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

	try {
		CryptoPP::Weak::MD5 hash;
		CryptoPP::HashFilter f(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))); //, false, 8);

		CryptoPP::FileSource(fToCheck.make_preferred().string().c_str(), true, new CryptoPP::Redirector(f));


		md5ret = digest;
		/*
		md5ret =
			md5->getHashFromFile(fToCheck.make_preferred().string());
		 */

	}
	catch(const CryptoPP::Exception& ex){
		std::cerr << "Hash error " << ex.what() << std::endl;
	}
	/*
	catch(hlException &e) {
		std::cerr << "hash error " << e.error_number() << ": "
				  << e.error_message() << std::endl;
	}*/

	//if( md5ret == md5db)
	if(digest == md5db)
		return true;

	std::cout << md5ret << " " << md5db << std::endl;
	return false;
}