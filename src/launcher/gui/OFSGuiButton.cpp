#include "OFSGuiButton.h"

#ifdef INCLUDE_RESOURCES
#define DATA(res_name) res_name##_bmp_data
#include "res/button_d.bmp.h"
#else
#define DATA(res_name) "../res/" #res_name ".bmp"
#endif


//###### OFSGuiButton ###########
OFSGuiButton::OFSGuiButton(SDL_Renderer *renderer, GuiActs actToLink,
						   const int &x, const int &y, const std::string &text, const ButtonTypes& buttonType)
	: OFSGuiImage() {
	bool white;
	int textSize;
	resData *spriteMapData;
	switch(buttonType){
		default:
			spriteMapData = &DATA(button_d);
		white = true;
		textSize = 80;
			break;
	}
#ifdef INCLUDE_RESOURCES
	SDL_RWops *data = SDL_RWFromMem((void *)SourceSansPro_Regular_ttf,
									SourceSansPro_Regular_ttf_len);
	TTF_Font *font = TTF_OpenFontRW(data, 1, text_size);
#else
	TTF_Font *font =
		TTF_OpenFont("../res/SourceSansPro-Regular.ttf", text_size);
#endif
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
		TTF_RenderText_Blended(font, text.c_str(), fontcolor);
	if(textureSurface == nullptr)
		throw SDLTTFException("OFSGuiText");
	_text.tex = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if(_text.tex == nullptr)
		throw SDLException("OFSGuiText");

	SDL_QueryTexture(_text.tex, nullptr, nullptr, &w, &h);
	_text.size.h = h;
	_text.size.w = w;
	if(x >= 0)
		_text.size.x = x;
	else
		_text.size.x = (WINDOW_WIDTH / 2) - (w / 2);
	_text.size.y = y;

	_text.src.h = h;
	_text.src.w = w;
	_text.src.x = 0;
	_text.src.y = 0;

#ifndef _WIN32
	SDL_FreeSurface(textureSurface); //WTF crashes on windows????
#endif

	_act = actToLink;
	_isClicked = false;
}

OFSGuiButton::~OFSGuiButton() {
}

void OFSGuiButton::getClickedDown() {

	int x, y, mouseState;
	mouseState = SDL_GetMouseState(&x, &y);
	if(mouseState == SDL_BUTTON(SDL_BUTTON_LEFT)) {

		if(x > _size.x && x < _size.x + _size.w) {
			if(y > _size.y && y < _size.y + _size.h) {
				_isClicked = true;
				setIndex(2); // Mouse was pressed down on button
			}
		}
	}
}

GuiActs OFSGuiButton::getClickedUp() {
	GuiActs ret = NOT_CLICKED;
	if(_isClicked) {
		setIndex(0);
		_isClicked = false;
		int x, y, mouseState;
		mouseState = SDL_GetMouseState(&x, &y);
		if(x > _size.x && x < _size.x + _size.w && y > _size.y &&
		   y < _size.y + _size.h) {
			setIndex(1);
			ret = _act;
		}
	}
	return ret;
}

void OFSGuiButton::getHover() {
	if(!_isClicked) {
		int x, y, mouseState;
		mouseState = SDL_GetMouseState(&x, &y);
		if(x > _size.x && x < _size.x + _size.w && y > _size.y &&
		   y < _size.y + _size.h)
			setIndex(1); // Hovering over
		else
			setIndex(0); // normal state
	}
}
