//
// Created by fenteale on 11/15/20.
//

#include "OFSVerifyIntegrity.h"

static hashwrapper *md5 = new md5wrapper();

bool verifyIntegrity(std::filesystem::path fToCheck, std::string md5db) {
	std::string md5ret = "";
	try {
		md5ret =
			md5->getHashFromFile(fToCheck.make_preferred().string());
	}
	catch(hlException &e) {
		std::cerr << "hash error " << e.error_number() << ": "
				  << e.error_message() << std::endl;
	}
	if( md5ret == md5db)
		return true;

	std::cout << md5ret << " " << md5db << std::endl;
	return false;
}