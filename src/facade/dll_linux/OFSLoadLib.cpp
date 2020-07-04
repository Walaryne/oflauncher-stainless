#include "OFSLoadLib.h"

void *realClientInterface(char const *name, int *err) {
    typedef void *(*cInt)(char const *name, int *err);
    void *handle = dlopen(steamPath.c_str(), RTLD_NOW);
	if(!handle) {
		std::cout << "Cant load real client library." << std::endl;
		std::cout << dlerror() << std::endl;
	}

	//typedef void *(*cInt)(char const *name, int *err);
	cInt realCIe = (cInt)dlsym(handle, "CreateInterface");
	char *error;
	if((error = dlerror()) != nullptr) {
		std::cout << "Cant resolve real interface." << std::endl;
		std::cout << error << std::endl;
	}

	void *hd = realCI(name, err);
	dlclose(handle);
    return hd;
}
