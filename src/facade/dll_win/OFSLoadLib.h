#include <Windows.h>
#define CREATEINTERFACE_PROCNAME "CreateInterface"

#define DLL_EXPORT extern "C" __declspec(dllexport)

void *realClientInterface(char const *name, int *err)