#include "OFSLoadLib.h"

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

void *realClientInterface(char const *name, int *err) {
    typedef void *(*cInt)(char const *name, int *err);
    //HINSTANCE handle = LoadLibraryEx("C:\\Users\\Fenteale\\Documents\\Projects\\ofd\\Open-Fortress-Source\\game\\open_fortress\\bin\\client_real.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH);  //this works
	HINSTANCE handle =
		 LoadLibraryExA("client_real.dll", nullptr,
		 LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR); //this aint workin.
	if(!handle) {
		std::cout << "Cant load real client library." << std::endl;
		ShowError("client_real.dll load error");
	}
	cInt realCI = (cInt)GetProcAddress(handle, "CreateInterface");
	if(!realClientInterface)
		std::cout << "Cant resolve real interface" << std::endl;
	void *hd = realCI(name, err);

    return hd;
}
