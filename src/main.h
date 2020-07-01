//
// Created by walaryne on 6/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_MAIN_H
#define OFLAUNCHER_STAINLESS_MAIN_H

#include "db/OFSDatabase.h"
#include "gui/OFSGui.h"
#include "net/OFSNet.h"
#include "steam/OFSPathDiscover.h"
#include <exception>
#include <filesystem>
#include <iostream>

#ifdef __linux__
#include <unistd.h>
#else
#include <direct.h>
#endif

namespace fs = std::filesystem;

#endif // OFLAUNCHER_STAINLESS_MAIN_H
