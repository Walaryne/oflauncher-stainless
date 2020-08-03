//
// Created by fenteale on 8/2/20.
//

#include "OFSGuiDirButton.h"

OFSGuiDirButton::OFSGuiDirButton(const std::string &name, const EmbedData imgData, SDL_Renderer *renderer, const int &x, const int &y, const ButtonTypes &buttonType) :
 OFSGuiButton(name, imgData, renderer, NOT_CLICKED, x, y, buttonType){

}

GuiActs OFSGuiDirButton::parseEvents(std::shared_ptr<OFSGuiEvent> ev) {
	if(ev->eventType == EVENT_SDL) {
		switch(ev->sdl.type) {
		case SDL_MOUSEBUTTONDOWN:
			if(ev->sdl.button.state == SDL_BUTTON(SDL_BUTTON_LEFT)) {
				if(ev->sdl.button.x > _size.x && ev->sdl.button.x < _size.x + _size.w) {
					if(ev->sdl.button.y > _size.y &&
					   ev->sdl.button.y < _size.y + _size.h) {
						_isClicked = true;
						setIndex(2); // Mouse was pressed down on button
					}
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if(_isClicked) {
				setIndex(0);
				_isClicked = false;
				if(ev->sdl.button.x > _size.x && ev->sdl.button.x < _size.x + _size.w &&
				   ev->sdl.button.y > _size.y && ev->sdl.button.y < _size.y + _size.h) {
					setIndex(1);
					NFD_OpenDialog( nullptr, nullptr, nullptr);
				}
			}
			break;
		case SDL_MOUSEMOTION:

			if(!_isClicked) {
				if(ev->sdl.motion.x > _size.x && ev->sdl.motion.x < _size.x + _size.w &&
				   ev->sdl.motion.y > _size.y && ev->sdl.motion.y < _size.y + _size.h)
					setIndex(1); // Hovering over
				else
					setIndex(0); // normal state
			}
			break;
		}
	}
	return NOT_CLICKED;
}