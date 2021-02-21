//
// Created by fenteale on 10/23/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUITHREAD_H
#define OFLAUNCHER_STAINLESS_OFSGUITHREAD_H

#include <string>
#include <vector>
#include <exception>
#include "OFSGui.h"
#include "../../shared/config/OFSConfig.h"
#include "../launchopt/OFSLaunchOpt.h"

extern SDL_sem * butDataLock;
extern SDL_sem * continueDataLock;
extern SDL_sem * verifyStateLock;

extern int butStateData;
extern float progData;
extern bool continueData;
extern bool firstTime;
extern int verifyState;

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
void simulateButton(GuiActs act);

#endif // OFLAUNCHER_STAINLESS_OFSGUITHREAD_H
