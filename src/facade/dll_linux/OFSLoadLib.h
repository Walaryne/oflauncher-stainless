#ifndef OFLAUNCHER_STAINLESS_OFSLOADLIB_H
#define OFLAUNCHER_STAINLESS_OFSLOADLIB_H

#include <dlfcn.h>
#include <iostream>
#include <unistd.h>

#define DLL_EXPORT extern "C" __attribute__((visibility("default")))

void *realClientInterface(char const *name, int *err, std::string steamPath);

void runLauncher(std::string steamPath);

#endif // OFLAUNCHER_STAINLESS_OFSLOADLIB_H