//
// Created by walaryne on 6/29/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSFACADE_H
#define OFLAUNCHER_STAINLESS_OFSFACADE_H


#include <iostream>
#include <string>

#include "../shared/steam/OFSPathDiscover.h"
#include "OFSLoadLib.h"

DLL_EXPORT void *CreateInterface(char const *name, int *err);

#endif // OFLAUNCHER_STAINLESS_OFSFACADE_H
