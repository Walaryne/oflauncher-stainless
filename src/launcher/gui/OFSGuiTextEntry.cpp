#include "OFSGuiTextEntry.h"

OFSGuiTextEntry::OFSGuiTextEntry(resData fontData, SDL_Renderer *renderer,
								 const std::string &text, const int &x,
								 const int &y, const int &width, const bool &startFocused)
	: OFSGuiText(fontData, renderer, text, 20, x + 5, y, false), _text(text), _focused(startFocused) {
	int w, h;

	SDL_Surface *textureSurface = SDL_CreateRGBSurfaceWithFormat(0, width, 25, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_FillRect(textureSurface, nullptr,
				 SDL_MapRGB(textureSurface->format, 0xFF, 0xFF, 0xFF));
	if(textureSurface == nullptr)
		throw SDLException("OFSGuiTextEntry");

	_backing = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if(_backing == nullptr)
		throw SDLException("OFSGuiTextEntry");

	SDL_QueryTexture(_backing, nullptr, nullptr, &w, &h);
	_backSize.h = h;
	_backSize.w = w;
	_backSize.x = x;
	_backSize.y = y;

	SDL_FreeSurface(textureSurface);
}

OFSGuiTextEntry::~OFSGuiTextEntry() {
	SDL_DestroyTexture(_backing);
}

GuiActs OFSGuiTextEntry::parseEvents(std::shared_ptr<OFSGuiEvent> ev)
{
	if(ev->eventType == EVENT_SDL) {
		switch(ev->sdl.type) {
		case SDL_MOUSEBUTTONDOWN:
			if(ev->sdl.button.state == SDL_BUTTON(SDL_BUTTON_LEFT)) {
				if(ev->sdl.button.x > _backSize.x &&
				   ev->sdl.button.x < _backSize.x + _backSize.w &&
				   ev->sdl.button.y > _backSize.y &&
				   ev->sdl.button.y < _backSize.y + _backSize.h) {
					_focused = true;
				} else {
					_focused = false;
				}
			}
			break;
		}
	}
	return NOT_CLICKED;
}

void OFSGuiTextEntry::renderCopy(SDL_Renderer *renderer) {
	if(_focused)
		SDL_RenderCopy(renderer, _backing, nullptr, &_backSize);
	SDL_RenderCopy(renderer, _texture, &_src, &_size);
}