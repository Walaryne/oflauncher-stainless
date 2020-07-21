#include "OFSGuiProgBar.h"
#include "res/barL.bmp.h"
#include "res/barM_n.bmp.h"
#include "res/barR.bmp.h"
#include <iostream>

#ifdef INCLUDE_RESOURCES
#define DATA(res_name) res_name##_bmp_data
#else
#define DATA(res_name) "../res/" #res_name ".bmp"
#endif

#define PIX_DRAW_PAST                                                          \
	2 // how many pixels to start drawing the loading bar progress into the end
	  // caps

SDL_Texture *OFSGuiProgBar::_loadSecondImg(resData dataToLoad,
										   SDL_Rect *srcRect,
										   SDL_Rect *sizeRect) {
#ifdef INCLUDE_RESOURCES
	SDL_RWops *rw = SDL_RWFromMem((void *)dataToLoad.buf, dataToLoad.len);
	SDL_Surface *textureSurface = SDL_LoadBMP_RW(rw, 1);
#else
	SDL_Surface *textureSurface = SDL_LoadBMP(dataToLoad.c_str());
#endif
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

OFSGuiProgBar::OFSGuiProgBar(resData data, SDL_Renderer *renderer, const int &x,
							 const int &y, const int &width)
	: OFSGuiImage(data, renderer, x, y, 0) {

	_renderer = renderer;

	_leftcap = _loadSecondImg(DATA(barL), &_leftSrc, &_leftSize);
	_rightcap = _loadSecondImg(DATA(barR), &_rightSrc, &_rightSize);
	_middleNone = _loadSecondImg(DATA(barM_n), &_mnSrc, &_mnSize);

	_barWidth = (width - _leftSize.w - _rightSize.w) + (PIX_DRAW_PAST * 2);
	if(x < 0)
		_xPos = (WINDOW_WIDTH / 2) - (width / 2);
	else
		_xPos = x;

	_leftSize.x = _xPos;
	_leftSize.y = y;
	_rightSize.x = _xPos + width - _rightSize.w;
	_rightSize.y = y;
	_mnSize.y = y;

	_progress = 0;
}

OFSGuiProgBar::~OFSGuiProgBar() {
	SDL_DestroyTexture(_leftcap);
	SDL_DestroyTexture(_rightcap);
	SDL_DestroyTexture(_middleNone);
}

void OFSGuiProgBar::renderCopy(SDL_Renderer *renderer) {
	int currProg = 0;
	int initialX = _xPos + _leftSize.w - PIX_DRAW_PAST;
	for(int x = initialX; x < initialX + _barWidth; x++) {
		if(currProg <= _progress) {
			_size.x = x;
			SDL_RenderCopy(renderer, _texture, &_src, &_size);
		} else {
			_mnSize.x = x;
			SDL_RenderCopy(renderer, _middleNone, &_mnSrc, &_mnSize);
		}
		currProg++;
	}
	SDL_RenderCopy(renderer, _leftcap, &_leftSrc, &_leftSize);
	SDL_RenderCopy(renderer, _rightcap, &_rightSrc, &_rightSize);
}

void OFSGuiProgBar::setProgress(const float &progress) {
	_progress = _barWidth * progress;
}