#include "OFSGuiText.h"

OFSGuiText::OFSGuiText(SDL_Renderer *renderer, const std::string &text,
					   const int &x, const int &y, const bool &white)
	: OFSGuiImage() {
	TTF_Font *font = TTF_OpenFont("../res/fonts/SourceSansPro-Regular.ttf", 20);
	SDL_Color fontcolor;
	if(white)
		fontcolor = {255, 255, 255, 255};
	else
		fontcolor = {0, 0, 0, 255};
	ok = true;
	subImages = 0;
	int w, h;
	SDL_Surface *textureSurface =
		TTF_RenderText_Solid(font, text.c_str(), fontcolor);
	if(textureSurface == nullptr) {
		ok = false;
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
		if(texture == nullptr) {
			ok = false;
		} else {
			SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
			size.h = h;
			size.w = w;
			size.x = x;
			size.y = y;

			src.h = h;
			src.w = w;
			src.x = 0;
			src.y = 0;
		}
		SDL_FreeSurface(textureSurface);
	}
}

OFSGuiText::~OFSGuiText() {
}