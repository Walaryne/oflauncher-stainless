#include "OFSGuiImage.h"

//####### OFSGuiImage ############
OFSGuiImage::OFSGuiImage(const std::string &name, resData data, SDL_Renderer *renderer, const int &x = 0,
						 const int &y = 0, const int &NumOfSubImages = 0) {
	_name = name;
	_renderer = renderer;
	_subImages = NumOfSubImages;

	SDL_RWops *rw = SDL_RWFromMem((void *)data.buf, data.len);
	SDL_Surface *textureSurface = SDL_LoadBMP_RW(rw, 1);

	int w, h;
	if(textureSurface == nullptr)
		throw SDLException("OFSGuiImage");
	_texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if(_texture == nullptr)
		throw SDLException("OFSGuiImage");

	SDL_QueryTexture(_texture, nullptr, nullptr, &w, &h);
	_size.h = h / (_subImages + 1);
	_size.w = w;
	if(x >= 0)
		_size.x = x;
	else
		_size.x = (WINDOW_WIDTH / 2) - (w / 2);
	_size.y = y;

	_src.h = h / (_subImages + 1);
	_src.w = w;
	_src.x = 0;
	_src.y = 0;

	SDL_FreeSurface(textureSurface);
}

SDL_Texture *OFSGuiImage::_loadSecondImg(resData dataToLoad,
										   SDL_Rect *srcRect,
										   SDL_Rect *sizeRect) {

	SDL_RWops *rw = SDL_RWFromMem((void *)dataToLoad.buf, dataToLoad.len);
	SDL_Surface *textureSurface = SDL_LoadBMP_RW(rw, 1);

	int w, h;
	if(textureSurface == nullptr)
		throw SDLException("OFSGuiImage");
	SDL_Texture *textureToLoad =
		SDL_CreateTextureFromSurface(_renderer, textureSurface);
	if(textureToLoad == nullptr)
		throw SDLException("OFSGuiImage");

	SDL_QueryTexture(textureToLoad, nullptr, nullptr, &w, &h);
	sizeRect->h = h;
	sizeRect->w = w;
	sizeRect->x = 0; // this is the x and y pos of the image
	sizeRect->y = 0;

	srcRect->h = h;
	srcRect->w = w;
	srcRect->x = 0;
	srcRect->y = 0;

	SDL_FreeSurface(textureSurface);

	return textureToLoad;
}

OFSGuiImage::~OFSGuiImage() {
	SDL_DestroyTexture(_texture);
}

std::string OFSGuiImage::getName() {
	return _name;
}

void OFSGuiImage::setIndex(const int &i) {
	if(i >= 0 && i <= _subImages)
		_src.y = _size.h * i;
}

void OFSGuiImage::renderCopy(SDL_Renderer *renderer) {
	if(_texture)
		SDL_RenderCopy(renderer, _texture, &_src, &_size);
}

GuiActs OFSGuiImage::parseEvents(std::shared_ptr<OFSGuiEvent> ev) {
	return NOT_CLICKED;
}

OFSGuiEvent OFSGuiImage::getData(GuiActs typeToGet){
	return OFSGuiEvent("", NO_EVENT, nullptr);
}