//
// Created by walaryne on 6/29/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSFACADE_H
#define OFLAUNCHER_STAINLESS_OFSFACADE_H

#include <iostream>

extern "C" {
	extern void *CreateInterface(char const *name, int *err);
};

#endif // OFLAUNCHER_STAINLESS_OFSFACADE_H
