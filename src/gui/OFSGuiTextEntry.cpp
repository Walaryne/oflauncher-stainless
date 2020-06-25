#include "OFSGuiTextEntry.h"

OFSGuiTextEntry::OFSGuiTextEntry(SDL_Renderer *renderer,
								 const std::string &text, const int &x,
								 const int &y, const int &width)
	: OFSGuiText(renderer, text, x + 5, y, false), text(text) {
	// SDL_Color backcolor = {255, 255, 255, 255};

	int w, h;
	Uint32 rmask, gmask, bmask, amask;

	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;

	SDL_Surface *textureSurface =
		SDL_CreateRGBSurface(0, width, 25, 32, rmask, gmask, bmask, amask);
	SDL_FillRect(textureSurface, nullptr,
				 SDL_MapRGB(textureSurface->format, 0xFF, 0xFF, 0xFF));
	if(textureSurface == nullptr) {
		ok = false;
	} else {
		backing = SDL_CreateTextureFromSurface(renderer, textureSurface);
		if(backing == nullptr) {
			ok = false;
		} else {
			SDL_QueryTexture(backing, nullptr, nullptr, &w, &h);
			backSize.h = h;
			backSize.w = w;
			backSize.x = x;
			backSize.y = y;

			backSrc.h = h;
			backSrc.w = w;
			backSrc.x = 0;
			backSrc.y = 0;
		}
		SDL_FreeSurface(textureSurface);
	}
}

OFSGuiTextEntry::~OFSGuiTextEntry() {
	SDL_DestroyTexture(backing);
}

void OFSGuiTextEntry::renderCopy(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, backing, &backSrc, &backSize);
	SDL_RenderCopy(renderer, texture, &src, &size);
}