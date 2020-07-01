#include "OFSGuiButton.h"

//###### OFSGuiButton ###########
OFSGuiButton::OFSGuiButton(const void* buf, unsigned int len,
						   SDL_Renderer *renderer, GuiActs actToLink,
						   const int &x = 0, const int &y = 0,
						   const int &NumOfSubImages = 0)
	: OFSGuiImage(buf, len, renderer, x, y, NumOfSubImages) {
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
