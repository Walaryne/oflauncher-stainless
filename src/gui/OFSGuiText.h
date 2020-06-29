#ifndef OFLAUNCHER_STAINLESS_OFSGUITEXT_H
#define OFLAUNCHER_STAINLESS_OFSGUITEXT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

#include "OFSGuiImage.h"

class OFSGuiText : public OFSGuiImage {
public:
	OFSGuiText(SDL_Renderer *renderer, const std::string &text,
			   const int &text_size = 20, const int &x = 0, const int &y = 0,
			   const bool &white = true);
	~OFSGuiText();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUITEXT_H