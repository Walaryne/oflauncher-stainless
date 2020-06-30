//
// Created by walaryne on 6/29/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSFACADE_H
#define OFLAUNCHER_STAINLESS_OFSFACADE_H

#include <dlfcn.h>
#include <iostream>
#include <string>

#include "../steam/OFSPathDiscover.h"

#ifdef DRAW_WINDOW
#include "SDL2/SDL.h"
#endif

extern "C" {
extern void *CreateInterface(char const *name, int *err);
};

#endif // OFLAUNCHER_STAINLESS_OFSFACADE_H
