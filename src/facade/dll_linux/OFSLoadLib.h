#include <dlfcn.h>

#define DLL_EXPORT extern "C" __attribute__((visibility("default")))

void *realClientInterface(char const *name, int *err);