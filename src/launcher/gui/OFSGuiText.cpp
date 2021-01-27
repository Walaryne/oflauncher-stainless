#include "OFSGuiText.h"

#define DROP_SHADOW_DISTANCE 2

OFSGuiText::OFSGuiText(const std::string &name, resData fontData, SDL_Renderer *renderer, const std::string &text,
					   const int &text_size, const int &x, const int &y,
					   const bool &white)
	: OFSGuiImage() {

	SDL_RWops *data = SDL_RWFromMem((void *)fontData.buf,
									fontData.len);
	_fontData = TTF_OpenFontRW(data, 1, text_size);

	if(_fontData == nullptr)
		throw SDLTTFException("OFSGuiText");

	SDL_Color fontcolor;
	SDL_Surface *backDrop = nullptr;
	SDL_Rect backSize;


	_subImages = 0;
	int w, h;
	if(text == "")
	{
		_texture = nullptr;
	}
	else {
		if(white) {
			fontcolor = {0xe0, 0x96, 0xff, 255};
			backDrop = TTF_RenderText_Blended(_fontData, text.c_str(), {0, 0, 0, 250});
			backSize.x = DROP_SHADOW_DISTANCE;
			backSize.y = DROP_SHADOW_DISTANCE;
			backSize.w = backDrop->w - DROP_SHADOW_DISTANCE;
			backSize.h = backDrop->h - DROP_SHADOW_DISTANCE;
		}
		else
			fontcolor = {0, 0, 0, 255};

		SDL_Surface *textureSurface = nullptr;
		/*
		if(backDrop != nullptr) {
			SDL_Surface * tSurface = TTF_RenderText_Blended(_fontData, text.c_str(), fontcolor);
			if(tSurface == nullptr)
				throw SDLTTFException("OFSGuiText");
			textureSurface = SDL_CreateRGBSurfaceWithFormat(0, tSurface->w, tSurface->h, 32, SDL_PIXELFORMAT_RGBA32);
			SDL_BlitSurface(backDrop, nullptr, textureSurface, &backSize);
			SDL_BlitSurface(tSurface, nullptr, textureSurface, nullptr);
			SDL_FreeSurface(tSurface);
		}
		else {
		 */
			textureSurface =
				TTF_RenderText_Blended(_fontData, text.c_str(), fontcolor);
			if(textureSurface == nullptr)
				throw SDLTTFException("OFSGuiText");
		//}
		_texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
		if(_texture == nullptr)
			throw SDLException("OFSGuiText");

		SDL_QueryTexture(_texture, nullptr, nullptr, &w, &h);
		_size.h = h;
		_size.w = w;
		if(x >= 0)
			_size.x = x;
		else
			_size.x = (WINDOW_WIDTH / 2) - (w / 2);
		_size.y = y;

		_src.h = h;
		_src.w = w;
		_src.x = 0;
		_src.y = 0;

		SDL_FreeSurface(textureSurface);
		SDL_FreeSurface(backDrop);
	}
	_renderer = renderer;
	_name = name;
}

OFSGuiText::~OFSGuiText() {
}
