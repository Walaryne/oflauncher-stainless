//
// Created by walaryne on 6/29/20.
//

#include "OFSFacade.h"

void *CreateInterface(char const *name, int *err) {
	static bool hasExec = false;
	static fs::path steamPath;

	if(!hasExec) {

#ifdef DRAW_WINDOW
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Window *window = SDL_GL_GetCurrentWindow();

		SDL_Surface *screen = SDL_GetWindowSurface(window);
		SDL_FillRect(screen, nullptr,
					 SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(500);
#endif
		std::cout << "LOL IT WORKS FAM" << std::endl;

		OFSPathDiscover sPath;
		std::string steamPathStr = sPath.getSourcemodsPath();
		steamPathStr += "/open_fortress/bin/client_real.so";
		steamPath = steamPathStr;
		steamPath = steamPath.make_preferred();

		std::cout << "OF path: " << steamPath << std::endl;
#ifdef DRAW_WINDOW
		SDL_FreeSurface(screen);
		SDL_Delay(5000);
#endif
		hasExec = true;
	}
	void *handle = dlopen(steamPath.c_str(), RTLD_NOW);
	if(!handle) {
		std::cout << "Cant load real client library." << std::endl;
		std::cout << dlerror() << std::endl;
	}

	typedef void *(*cInt)(char const *name, int *err);
	cInt realClientInterface = (cInt)dlsym(handle, "CreateInterface");
	char *error;
	if((error = dlerror()) != nullptr) {
		std::cout << "Cant resolve real interface." << std::endl;
		std::cout << error << std::endl;
	}

	void *hd = realClientInterface(name, err);
	dlclose(handle);

	return hd;
}