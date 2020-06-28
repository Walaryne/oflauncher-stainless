#include "OFSGuiText.h"

OFSGuiText::OFSGuiText(SDL_Renderer *renderer, const std::string &text,
					   const int &x, const int &y, const bool &white)
	: OFSGuiImage() {
	TTF_Font *font = TTF_OpenFont("../res/fonts/SourceSansPro-Regular.ttf", 20);
	if(font == nullptr)
		throw SDLTTFException("OFSGuiText");

	SDL_Color fontcolor;
	if(white)
		fontcolor = {255, 255, 255, 255};
	else
		fontcolor = {0, 0, 0, 255};

	_subImages = 0;
	int w, h;
	SDL_Surface *textureSurface =
		TTF_RenderText_Solid(font, text.c_str(), fontcolor);
	if(textureSurface == nullptr)
		throw SDLTTFException("OFSGuiText");
	_texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if(_texture == nullptr)
		throw SDLException("OFSGuiText");

	SDL_QueryTexture(_texture, nullptr, nullptr, &w, &h);
	_size.h = h;
	_size.w = w;
	_size.x = x;
	_size.y = y;

	_src.h = h;
	_src.w = w;
	_src.x = 0;
	_src.y = 0;

	SDL_FreeSurface(textureSurface);
}

OFSGuiText::~OFSGuiText() {
}