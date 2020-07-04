#include "OFSLoadLib.h"

void *realClientInterface(char const *name, int *err, std::string steamPath) {
	steamPath += "/client_real.so";

	typedef void *(*cInt)(char const *name, int *err);
	void *handle = dlopen(steamPath.c_str(), RTLD_NOW);
	if(!handle) {
		std::cout << "Cant load real client library." << std::endl;
		std::cout << dlerror() << std::endl;
	}

	cInt realCI = (cInt)dlsym(handle, "CreateInterface");
	char *error;
	if((error = dlerror()) != nullptr) {
		std::cout << "Cant resolve real interface." << std::endl;
		std::cout << error << std::endl;
	}

	void *hd = realCI(name, err);
	dlclose(handle);
	return hd;
}

void runLauncher(std::string steamPath) {
	steamPath += "/oflauncher_stainless";
	// execlp(steamPath.c_str(), nullptr);  //this doesnt work quite right yet,
	// it tries to load libs from steamrt
}