//
// Created by fenteale on 10/23/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUITHREAD_H
#define OFLAUNCHER_STAINLESS_OFSGUITHREAD_H

#include <string>
#include <exception>
#include "OFSGui.h"
#include "../../shared/config/OFSConfig.h"

extern SDL_sem * butDataLock;
extern SDL_sem * continueDataLock;

extern int butStateData;
extern float progData;
extern bool continueData;

#define TRYCATCHERR_START() try {

#define TRYCATCHERR_END(errMsg)                                                \
	}                                                                          \
	catch(std::exception & e) {                                                \
		std::string error_msg = errMsg "\n";                                   \
		error_msg.append(e.what());                                            \
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot Connect",       \
								 error_msg.c_str(), nullptr);                  \
	}

int doGui(void *ptr);

#endif // OFLAUNCHER_STAINLESS_OFSGUITHREAD_H
