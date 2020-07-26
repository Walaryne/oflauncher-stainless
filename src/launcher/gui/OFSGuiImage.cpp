#include "OFSGuiImage.h"

//####### OFSGuiImage ############
OFSGuiImage::OFSGuiImage(resData data, SDL_Renderer *renderer, const int &x = 0,
						 const int &y = 0, const int &NumOfSubImages = 0) {
	_subImages = NumOfSubImages;
#ifdef INCLUDE_RESOURCES
	SDL_RWops *rw = SDL_RWFromMem((void *)data.buf, data.len);
	SDL_Surface *textureSurface = SDL_LoadBMP_RW(rw, 1);
#else
	SDL_Surface *textureSurface = SDL_LoadBMP(data.c_str());
#endif
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

OFSGuiImage::~OFSGuiImage() {
	SDL_DestroyTexture(_texture);
}

void OFSGuiImage::setIndex(const int &i) {
	if(i >= 0 && i <= _subImages)
		_src.y = _size.h * i;
}

void OFSGuiImage::render(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, _texture, &_src, &_size);
}

void OFSGuiImage::onEvent(std::shared_ptr<GuiEvent> e) {
	// printf("Recieved GUI event\n");
	if(e->type == MOUSE_DOWN) {
		std::shared_ptr<MouseGuiEvent> me = std::dynamic_pointer_cast<MouseGuiEvent>(e);
    	// printf("Mouse Coords: %i %i\n", me->x, me->y);
	}
}

// void OFSGuiImage::getClickedDown() {
// }

// GuiActs OFSGuiImage::getClickedUp() {
// 	return NOT_CLICKED;
// }

// void OFSGuiImage::getHover() {
// }