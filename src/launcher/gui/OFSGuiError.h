#ifndef OFLAUNCHER_STAINLESS_OFSGUIERROR_H
#define OFLAUNCHER_STAINLESS_OFSGUIERROR_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <stdexcept>

class SDLException : public std::runtime_error {
private:
	static std::string _make_err(const char *msg);

public:
	SDLException(const char *msg = "");
};

class SDLTTFException : public std::runtime_error {
private:
	static std::string _make_err(const char *msg);

public:
	SDLTTFException(const char *msg = "");
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIERROR_H