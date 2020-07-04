#include "OFSGuiError.h"

SDLException::SDLException(const char *msg)
	: std::runtime_error(_make_err(msg)) {
}
std::string SDLException::_make_err(const char *msg) {
	std::string ret("");
	if(strcmp(msg, "")) {
		ret.append(msg);
		if(strcmp(SDL_GetError(), ""))
			ret.append(": ");
	}
	if(strcmp(SDL_GetError(), ""))
		ret.append(SDL_GetError());
	return ret;
}

SDLTTFException::SDLTTFException(const char *msg)
	: std::runtime_error(_make_err(msg)) {
}
std::string SDLTTFException::_make_err(const char *msg) {
	std::string ret("");
	if(strcmp(msg, "")) {
		ret.append(msg);
		if(strcmp(TTF_GetError(), ""))
			ret.append(": ");
	}
	if(strcmp(TTF_GetError(), ""))
		ret.append(TTF_GetError());
	return ret;
}