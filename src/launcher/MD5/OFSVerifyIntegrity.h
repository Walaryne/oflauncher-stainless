//
// Created by fenteale on 11/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSVERIFYINTEGRITY_H
#define OFLAUNCHER_STAINLESS_OFSVERIFYINTEGRITY_H

#include <string>
#include "OFFilesystem.h"
#include <iostream>
#include <fstream>
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "cryptopp/md5.h"
//#include "../hashlib2plus/hashlibpp.h"


bool verifyIntegrity(fs::path fToCheck, std::string md5db);

#endif // OFLAUNCHER_STAINLESS_OFSVERIFYINTEGRITY_H
