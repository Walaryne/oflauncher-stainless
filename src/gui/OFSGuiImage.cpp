#include "OFSGuiImage.h"

//####### OFSGuiImage ############
OFSGuiImage::OFSGuiImage(const std::string &image_file, SDL_Renderer *renderer,
						 const int &x = 0, const int &y = 0,
						 const int &NumOfSubImages = 0) {
	ok = true;
	subImages = NumOfSubImages;
	int w, h;
	SDL_Surface *textureSurface = SDL_LoadBMP(image_file.c_str());
	if(textureSurface == nullptr) {
		ok = false;
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
		if(texture == nullptr) {
			ok = false;
		} else {
			SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
			size.h = h / (subImages + 1);
			size.w = w;
			size.x = x;
			size.y = y;

			src.h = h / (subImages + 1);
			src.w = w;
			src.x = 0;
			src.y = 0;
		}
		SDL_FreeSurface(textureSurface);
	}
}

OFSGuiImage::~OFSGuiImage() {
	SDL_DestroyTexture(texture);
}

bool OFSGuiImage::isOk() {
	return ok;
}

void OFSGuiImage::setIndex(const int &i) {
	if(i >= 0 && i <= subImages)
		src.y = size.h * i;
}

void OFSGuiImage::renderCopy(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, texture, &src, &size);
}

void OFSGuiImage::getClickedDown() {
}

GuiActs OFSGuiImage::getClickedUp() {
	return NOT_CLICKED;
}

void OFSGuiImage::getHover() {
}