//
// Created by fenteale on 11/11/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGAMEINFO_H
#define OFLAUNCHER_STAINLESS_OFSGAMEINFO_H

#include <string>
#include "OFFilesystem.h"
#include <fstream>
#include "../../shared/steam/OFSSteam.h"

void writeGameInfo(fs::path giPath, OFSSteam* steam);

#endif // OFLAUNCHER_STAINLESS_OFSGAMEINFO_H
