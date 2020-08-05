#include "OFSGuiTextEntry.h"
#include <iostream>

#define TEXT_EDIT_SIZE	20
#define TEXT_EDGE_PADDING 5

OFSGuiTextEntry::OFSGuiTextEntry(const std::string &name, resData fontData, SDL_Renderer *renderer,
								 const std::string &text, const int &x,
								 const int &y, const int &width, const bool &startFocused)
	: OFSGuiText(name, fontData, renderer, text, TEXT_EDIT_SIZE, x + TEXT_EDGE_PADDING, y, false), _text(text), _focused(startFocused) {
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

	textureSurface = SDL_CreateRGBSurfaceWithFormat(0, 2, 18, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_FillRect(textureSurface, nullptr,
				 SDL_MapRGB(textureSurface->format, 0, 0, 0));
	_cursor = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if(!_cursor)
		throw SDLException("OFSGuiTextEntry");

	SDL_QueryTexture(_cursor, nullptr, nullptr, &w, &h);
	_cursorSize.h = h;
	_cursorSize.w = w;
	_cursorSize.x = _size.x + _size.w + 1;
	_cursorSize.y = _size.y + 4;

	SDL_FreeSurface(textureSurface);
}

OFSGuiTextEntry::~OFSGuiTextEntry() {
	SDL_DestroyTexture(_backing);
}

void OFSGuiTextEntry::_updateText() {
	if(_text == "")
	{
		_texture = nullptr;
	}
	else {
		if(_fontData == nullptr)
			throw SDLTTFException("OFSGuiTextEntry");

		SDL_Color fontcolor = {0, 0, 0, 255};

		_subImages = 0;
		int w, h;
		SDL_Surface *textureSurface =
			TTF_RenderText_Blended(_fontData, _text.c_str(), fontcolor);
		if(textureSurface == nullptr)
			throw SDLTTFException("OFSGuiTextEntry");
		_texture = SDL_CreateTextureFromSurface(_renderer, textureSurface);
		if(_texture == nullptr)
			throw SDLException("OFSGuiTextEntry");

		SDL_QueryTexture(_texture, nullptr, nullptr, &w, &h);
		_size.h = h;
		_size.w = w;

		_src.h = h;
		if(_backSize.w - (TEXT_EDGE_PADDING * 2) >= _size.w) {
			_src.w = w;
			_src.x = 0;
		}
		else {
			_src.w = _backSize.w - (TEXT_EDGE_PADDING * 2);
			_src.x = _size.w - (_backSize.w - TEXT_EDGE_PADDING*2);
			_size.w = _backSize.w - (TEXT_EDGE_PADDING * 2);
		}

		_src.y = 0;

		SDL_FreeSurface(textureSurface);

		_cursorSize.x = _size.x + _size.w + 1;
	}
}

GuiActs OFSGuiTextEntry::parseEvents(std::shared_ptr<OFSGuiEvent> ev)
{
	if(ev->eventType == EVENT_SDL) {
		SDL_Event * sdle = (SDL_Event *)ev->data;
		switch(sdle->type) {
		case SDL_MOUSEBUTTONDOWN:
			if(sdle->button.state == SDL_BUTTON(SDL_BUTTON_LEFT)) {
				if(sdle->button.x > _backSize.x &&
					sdle->button.x < _backSize.x + _backSize.w &&
					sdle->button.y > _backSize.y &&
					sdle->button.y < _backSize.y + _backSize.h) {
					SDL_StopTextInput();
					SDL_StartTextInput();
					_focused = true;
					_showCursor = true;
					_toggleCursorTick = SDL_GetTicks() + 1000;
				} else {
					_showCursor = false;
					_focused = false;
				}
			}
			break;
		}
		if(_focused) {
			switch(sdle->type) {
				/*  I dont think this is what we want?
			case SDL_TEXTEDITING:
				_text = ev->sdl.edit.text;
				_updateTextNow = true;

				break;
				 */
			case SDL_TEXTINPUT:
				_text += sdle->text.text;
				_updateTextNow = true;
				_showCursor = true;
				_toggleCursorTick = SDL_GetTicks() + 1000;
				break;
			case SDL_KEYDOWN:
				if(sdle->key.keysym.sym == SDLK_BACKSPACE) {
					if(_text != "") {
						_text.resize(_text.size() - 1, ' ');
						_updateTextNow = true;
						_cursorSize.x = _size.x + 1;
					}
					_showCursor = true;
					_toggleCursorTick = SDL_GetTicks() + 1000;
				}
				break;

			}
		}
	}
	return NOT_CLICKED;
}

void OFSGuiTextEntry::renderCopy(SDL_Renderer *renderer) {
	if(_updateTextNow) {
		_updateText();
		_updateTextNow = false;
	}
	if(SDL_GetTicks() >= _toggleCursorTick && _focused) {
		_showCursor = !_showCursor;
		_toggleCursorTick = SDL_GetTicks() + 1000;
	}
	SDL_RenderCopy(renderer, _backing, nullptr, &_backSize);
	if(_texture)
		SDL_RenderCopy(renderer, _texture, &_src, &_size);
	if(_showCursor)
		SDL_RenderCopy(renderer, _cursor, nullptr, &_cursorSize);
}

OFSGuiEvent OFSGuiTextEntry::getData(GuiActs typeToGet){
	if(typeToGet == DATA_TEXT)
		return OFSGuiEvent(_name, EVENT_DATA_TEXT, &_text);
	return OFSGuiEvent(nullptr, NO_EVENT, nullptr);
}