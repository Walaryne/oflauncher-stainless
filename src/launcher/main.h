//
// Created by walaryne on 6/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_MAIN_H
#define OFLAUNCHER_STAINLESS_MAIN_H

#include "db/OFSDatabase.h"
#include "gui/OFSGui.h"
#include "net/OFSNet.h"
#include "../shared/steam/OFSPathDiscover.h"
#include <exception>
#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#include <Windows.h>
#undef main
#else
#include <unistd.h>
#endif

namespace fs = std::filesystem;

#endif // OFLAUNCHER_STAINLESS_MAIN_H
