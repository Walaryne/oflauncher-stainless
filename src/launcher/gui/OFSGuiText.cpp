#include "OFSGuiText.h"


OFSGuiText::OFSGuiText(resData fontData, SDL_Renderer *renderer, const std::string &text,
					   const int &text_size, const int &x, const int &y,
					   const bool &white)
	: OFSGuiImage() {
#ifdef INCLUDE_RESOURCES
	SDL_RWops *data = SDL_RWFromMem((void *)fontData.buf,
									fontData.len);
	_fontData = TTF_OpenFontRW(data, 1, text_size);
#else
	fs::path p = fs::current_path();
	p += "/" + fontData;
	_fontData =
		TTF_OpenFont(p.make_preferred().string().c_str(), text_size);
#endif
	if(_fontData == nullptr)
		throw SDLTTFException("OFSGuiText");

	SDL_Color fontcolor;
	if(white)
		fontcolor = {255, 255, 255, 255};
	else
		fontcolor = {0, 0, 0, 255};

	_subImages = 0;
	int w, h;
	if(text == "")
	{
		_texture == nullptr;
	}
	else {
		SDL_Surface *textureSurface =
			TTF_RenderText_Blended(_fontData, text.c_str(), fontcolor);
		if(textureSurface == nullptr)
			throw SDLTTFException("OFSGuiText");
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
	}
	_renderer = renderer;
}

OFSGuiText::~OFSGuiText() {
}
