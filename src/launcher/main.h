//
// Created by walaryne on 6/15/20.
//

#ifndef OFLAUNCHER_STAINLESS_MAIN_H
#define OFLAUNCHER_STAINLESS_MAIN_H

#include "../shared/steam/OFSPathDiscover.h"
#include "db/OFSDatabase.h"
#include "gui/OFSGui.h"
#include "net/OFSNet.h"
#include "../updater/OFUpdater.h"
#include <exception>
#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#undef main
#else
#include <unistd.h>
#endif

namespace fs = std::filesystem;

#define TRYCATCHERR_START() try {

#define TRYCATCHERR_END(errMsg)                                                \
	}                                                                          \
	catch(std::exception & e) {                                                \
		std::string error_msg = errMsg "\n";                                   \
		error_msg.append(e.what());                                            \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot Connect",       \
								 error_msg.c_str(), nullptr);                  \
	}
#endif // OFLAUNCHER_STAINLESS_MAIN_H
