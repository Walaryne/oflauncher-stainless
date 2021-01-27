//
// Created by fenteale on 11/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSVERIFYINTEGRITY_H
#define OFLAUNCHER_STAINLESS_OFSVERIFYINTEGRITY_H

#include <string>
#include <experimental/filesystem>
#include <iostream>
#include "../hashlib2plus/hashlibpp.h"

bool verifyIntegrity(std::experimental::filesystem::path fToCheck, std::string md5db);

#endif // OFLAUNCHER_STAINLESS_OFSVERIFYINTEGRITY_H
