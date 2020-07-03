//
// Created by walaryne on 6/29/20.
//

#include "OFSFacade.h"

#ifdef _WIN32
void ShowError(const std::string &msg) {
	LPSTR dumbWindowsFormat = nullptr;
	size_t size = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&dumbWindowsFormat, 0, NULL);
	std::string err(dumbWindowsFormat, size);
	MessageBox(nullptr, err.c_str(), msg.c_str(),
			   MB_OK);
}
#endif


void *CreateInterface(char const *name, int *err) {
	static bool hasExec = false;
	static fs::path steamPath;

	typedef void *(*cInt)(char const *name, int *err);

	if(!hasExec) {

#ifdef DRAW_WINDOW
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Window *window = SDL_GL_GetCurrentWindow();
		SDL_Surface *screen = nullptr;
		if(window) {

			screen = SDL_GetWindowSurface(window);
			SDL_FillRect(screen, nullptr,
						 SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(500);
		}
#endif
		std::cout << "LOL IT WORKS FAM" << std::endl;

		OFSPathDiscover sPath;
		std::string steamPathStr = sPath.getSourcemodsPath();
		steamPathStr += "/open_fortress/bin/client_real.so";
		steamPath = steamPathStr;
		steamPath = steamPath.make_preferred();

		std::cout << "OF path: " << steamPath << std::endl;
#ifdef DRAW_WINDOW
		if(screen) {

			SDL_FreeSurface(screen);
			SDL_Delay(5000);
		}
#endif
		hasExec = true;
	}
#ifdef _WIN32
	//HINSTANCE handle = LoadLibraryEx("C:\\Users\\Fenteale\\Documents\\Projects\\ofd\\Open-Fortress-Source\\game\\open_fortress\\bin\\client_real.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH);  //this works
	HINSTANCE handle =
		 LoadLibraryExA("client_real.dll", nullptr,
		 LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR); //this aint workin.
	if(!handle) {
		std::cout << "Cant load real client library." << std::endl;
		ShowError("client_real.dll load error");
	}
	cInt realClientInterface = (cInt)GetProcAddress(handle, "CreateInterface");
	if(!realClientInterface)
		std::cout << "Cant resolve real interface" << std::endl;
	void *hd = realClientInterface(name, err);
#else
	void *handle = dlopen(steamPath.c_str(), RTLD_NOW);
	if(!handle) {
		std::cout << "Cant load real client library." << std::endl;
		std::cout << dlerror() << std::endl;
	}

	//typedef void *(*cInt)(char const *name, int *err);
	cInt realClientInterface = (cInt)dlsym(handle, "CreateInterface");
	char *error;
	if((error = dlerror()) != nullptr) {
		std::cout << "Cant resolve real interface." << std::endl;
		std::cout << error << std::endl;
	}

	void *hd = realClientInterface(name, err);
	dlclose(handle);
#endif

	return hd;
}