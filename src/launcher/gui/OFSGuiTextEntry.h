#ifndef OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H
#define OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

#include "OFSGuiText.h"

class OFSGuiTextEntry : public OFSGuiText {
private:
	SDL_Texture *_backing;
	SDL_Rect _backSrc;
	SDL_Rect _backSize;

	std::string _text;
	bool _focused;

public:
	OFSGuiTextEntry(SDL_Renderer *renderer, const std::string &text,
					const int &x, const int &y, const int &width);
	~OFSGuiTextEntry();

	void renderCopy(SDL_Renderer *renderer);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H