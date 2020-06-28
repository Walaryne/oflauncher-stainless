#include "OFSGuiTextEntry.h"

OFSGuiTextEntry::OFSGuiTextEntry(SDL_Renderer *renderer,
								 const std::string &text, const int &x,
								 const int &y, const int &width)
	: OFSGuiText(renderer, text, x + 5, y, false), _text(text) {
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
	if(textureSurface == nullptr)
		throw SDLException("OFSGuiTextEntry");

	_backing = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if(_backing == nullptr)
		throw SDLException("OFSGuiTextEntry");

	SDL_QueryTexture(_backing, nullptr, nullptr, &w, &h);
	_backSize.h = h;
	_backSize.w = w;
	_backSize.x = x;
	_backSize.y = y;

	_backSrc.h = h;
	_backSrc.w = w;
	_backSrc.x = 0;
	_backSrc.y = 0;

	SDL_FreeSurface(textureSurface);
}

OFSGuiTextEntry::~OFSGuiTextEntry() {
	SDL_DestroyTexture(_backing);
}

void OFSGuiTextEntry::renderCopy(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, _backing, &_backSrc, &_backSize);
	SDL_RenderCopy(renderer, _texture, &_src, &_size);
}