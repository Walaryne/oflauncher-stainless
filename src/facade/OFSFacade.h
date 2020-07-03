//
// Created by walaryne on 6/29/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSFACADE_H
#define OFLAUNCHER_STAINLESS_OFSFACADE_H


#if defined(_WIN32)
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C" __attribute__((visibility("default")))
#endif

#ifndef _WIN32
#include <dlfcn.h>
#else
#include <Windows.h>
#define CREATEINTERFACE_PROCNAME "CreateInterface"


#endif
#include <iostream>
#include <string>

#include "../steam/OFSPathDiscover.h"

#ifdef DRAW_WINDOW
#include "SDL2/SDL.h"
#endif
/*
extern "C" {
extern void *CreateInterface(char const *name, int *err);
};*/

DLL_EXPORT void *CreateInterface(char const *name, int *err);

#endif // OFLAUNCHER_STAINLESS_OFSFACADE_H
