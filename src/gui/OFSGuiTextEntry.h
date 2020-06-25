#ifndef OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H
#define OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

#include "OFSGuiText.h"

class OFSGuiTextEntry : public OFSGuiText {
private:
	SDL_Texture *backing;
	SDL_Rect backSrc;
	SDL_Rect backSize;

	std::string text;
	bool focused;

public:
	OFSGuiTextEntry(SDL_Renderer *renderer, const std::string &text,
					const int &x, const int &y, const int &width);
	~OFSGuiTextEntry();

	void renderCopy(SDL_Renderer *renderer);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H