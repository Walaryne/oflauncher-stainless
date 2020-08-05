//
// Created by fenteale on 8/2/20.
//

#include "OFSGuiDirButton.h"

OFSGuiDirButton::OFSGuiDirButton(const std::string &name, const EmbedData imgData, SDL_Renderer *renderer, const int &x, const int &y, const ButtonTypes &buttonType) :
 OFSGuiButton(name, imgData, renderer, NOT_CLICKED, x, y, buttonType){

}

GuiActs OFSGuiDirButton::parseEvents(std::shared_ptr<OFSGuiEvent> ev) {
	if(ev->eventType == EVENT_SDL) {
		SDL_Event * sdle = (SDL_Event *)ev->data;
		switch(sdle->type) {
		case SDL_MOUSEBUTTONDOWN:
			if(sdle->button.state == SDL_BUTTON(SDL_BUTTON_LEFT)) {
				if(sdle->button.x > _size.x && sdle->button.x < _size.x + _size.w) {
					if(sdle->button.y > _size.y &&
						sdle->button.y < _size.y + _size.h) {
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
				if(sdle->button.x > _size.x && sdle->button.x < _size.x + _size.w &&
					sdle->button.y > _size.y && sdle->button.y < _size.y + _size.h) {
					setIndex(1);
					NFD_OpenDialog( nullptr, nullptr, nullptr);
				}
			}
			break;
		case SDL_MOUSEMOTION:

			if(!_isClicked) {
				if(sdle->motion.x > _size.x && sdle->motion.x < _size.x + _size.w &&
					sdle->motion.y > _size.y && sdle->motion.y < _size.y + _size.h)
					setIndex(1); // Hovering over
				else
					setIndex(0); // normal state
			}
			break;
		}
	}
	return NOT_CLICKED;
}