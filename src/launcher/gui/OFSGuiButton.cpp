#include "OFSGuiButton.h"

//#include "res/button_d.bmp.h"
#include "res/button_idle.bmp.h"
#include "res/button_hover.bmp.h"
#include "res/button_press.bmp.h"
#include "res/primary_idle.bmp.h"
#include "res/primary_hover.bmp.h"
#include "res/primary_press.bmp.h"
#define BUTDATA(res_name) & res_name##_bmp_data


#define TEXT_BUMP_VERT 2
#define TEXT_BUMP_HOR  2
#define DROP_SHADOW_DISTANCE 2


//###### OFSGuiButton ###########
OFSGuiButton::OFSGuiButton(const std::string &name, resData fontData, SDL_Renderer *renderer, GuiActs actToLink,
						   const int &x, const int &y, const std::string &text, const int fontSize)
	: OFSGuiImage() {
	bool white, crop, shadow;
	int textTopOffset = 0; // the bigger the button, the more space it looks like there is empty on the bottom.

	SDL_RWops *data = SDL_RWFromMem((void *)(fontData.buf), fontData.len);
	TTF_Font *font = TTF_OpenFontRW(data, 1, fontSize);

	if(font == nullptr)
		throw SDLTTFException("OFSGuiButton");

	SDL_Surface *textSurface = nullptr;


	SDL_Surface *textSurfaceNoCrop =
		TTF_RenderText_Blended(font, text.c_str(), {0xe0, 0x96, 0xff, 255});
	SDL_Surface *textSurfaceSel =
		TTF_RenderText_Blended(font, text.c_str(), {0xff, 0xff, 0xff, 255});
	if(!textSurfaceNoCrop || !textSurfaceSel)
		throw SDLTTFException("OFSGuiButton");

	textSurface = SDL_CreateRGBSurfaceWithFormat(
		0, textSurfaceNoCrop->w, textSurfaceNoCrop->h, 32,
		SDL_PIXELFORMAT_RGBA32);
	SDL_Rect textCrop;
	textCrop.x = 0;
	//textCrop.y = -fontSize/3;
	textCrop.y = textTopOffset;
	textCrop.w = textSurfaceNoCrop->w;
	textCrop.h = textSurfaceNoCrop->h;
	SDL_BlitSurface(textSurfaceNoCrop, nullptr, textSurface, &textCrop);
	SDL_FreeSurface(textSurfaceNoCrop);

	if(textSurface == nullptr)
		throw SDLTTFException("OFSGuiText");

	SDL_Surface* arrowSurf = TTF_RenderText_Blended(font, ">", {0xe0, 0x96, 0xff, 255});
	_arrowRect.x = x - arrowSurf->w;
	_arrowRect.y = y;
	_arrowRect.w = arrowSurf->w;
	_arrowRect.h = arrowSurf->h;
	_arrow = SDL_CreateTextureFromSurface(renderer, arrowSurf);
	SDL_FreeSurface(arrowSurf);

	_renderer = renderer;
	_act = actToLink;
	_name = name;

	_isImgBut = false;
	_finishLoading(textSurface, textSurfaceSel, x, y, shadow);
}

OFSGuiButton::OFSGuiButton(const std::string &name, const EmbedData imgData, const EmbedData imgDataSel, SDL_Renderer *renderer, GuiActs actToLink, const int &x, const int &y, const ButtonTypes &buttonType)
	: OFSGuiImage() {

	SDL_RWops *data = SDL_RWFromMem((void *)(imgData.buf), imgData.len);
	SDL_Surface *textSurface = SDL_LoadBMP_RW(data, 1);
	SDL_RWops *data_sel = SDL_RWFromMem((void *)(imgDataSel.buf), imgDataSel.len);
	SDL_Surface *textSurfaceSel = SDL_LoadBMP_RW(data_sel, 1);

	if(textSurface == nullptr)
		throw SDLException("OFSGuiText");

	_renderer = renderer;
	_act = actToLink;
	_name = name;

	_isImgBut = true;

	_finishLoading(textSurface, textSurfaceSel, x, y, false);
}

void OFSGuiButton::_finishLoading(SDL_Surface *textSurface, SDL_Surface* selectedSurface, const int &x, const int &y, const bool &shadow) {
	int fullWidth = textSurface->w;// + LEFT_BORDER_INSET + RIGHT_BORDER_INSET;
	int fullHeight = textSurface->h; //+ TOP_BORDER_INSET + BOTTOM_BORDER_INSET;
	//SDL_Surface *textureSurface = SDL_CreateRGBSurfaceWithFormat(0, fullWidth, fullHeight * 3, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_Surface *textureSurface = SDL_CreateRGBSurfaceWithFormat(0, fullWidth, fullHeight * 3, 32, textSurface->format->format);

	SDL_Surface *textureSurface_tmp = SDL_CreateRGBSurfaceWithFormat(0, fullWidth, fullHeight, 32, textSurface->format->format);
	/*
	//blitNineSliceToSurface(spriteSurface_d, textureSurface_tmp, fullWidth, fullHeight);
	SDL_Rect paster = {0, 0, fullWidth, fullHeight};
	SDL_BlitSurface(textureSurface_tmp, nullptr, textureSurface, &paster);

	//blitNineSliceToSurface(spriteSurface_h, textureSurface_tmp, fullWidth, fullHeight);
	paster.y += fullHeight;
	SDL_BlitSurface(textureSurface_tmp, nullptr, textureSurface, &paster);

	//blitNineSliceToSurface(spriteSurface_c, textureSurface_tmp, fullWidth, fullHeight);
	paster.y += fullHeight;
	SDL_BlitSurface(textureSurface_tmp, nullptr, textureSurface, &paster);
	 */

	SDL_Rect textRect;
	textRect.x = 0;//LEFT_BORDER_INSET;
	textRect.y = 0; //TOP_BORDER_INSET;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);

	textRect.y += fullHeight;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);

	//textRect.y += fullHeight + TEXT_BUMP_VERT;
	//textRect.x += TEXT_BUMP_HOR;
	textRect.y += fullHeight;
	SDL_BlitSurface(selectedSurface, nullptr, textureSurface, &textRect);

	_texture = SDL_CreateTextureFromSurface(_renderer, textureSurface);
	if(_texture == nullptr)
		throw SDLException("OFSGuiText");


	_subImages = 2;

	int w, h;
	//set texture pos and stuff
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
	SDL_FreeSurface(textureSurface_tmp);

	_isHovered = false;
}

GuiActs OFSGuiButton::parseEvents(std::shared_ptr<OFSGuiEvent> ev) {
	GuiActs ret = NOT_CLICKED;
	if(ev->eventType == EVENT_SDL && (ev->name == _name || ev->name == "all")) {
		std::shared_ptr<SDL_Event> sdle = std::static_pointer_cast<SDL_Event>(ev->data);
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
					ret = _act;
					_clickedOnAction();
				}
			}
			break;
		case SDL_MOUSEMOTION:

			if(!_isClicked) {
				if(sdle->motion.x > _size.x && sdle->motion.x < _size.x + _size.w &&
					sdle->motion.y > _size.y && sdle->motion.y < _size.y + _size.h) {
					setIndex(1); // Hovering over
					_isHovered = true;
				}
				else {
					setIndex(0); // normal state
					_isHovered = false;
				}

			}
			break;
		}
	}
	return ret;
}

void OFSGuiButton::renderCopy(SDL_Renderer *renderer) {
	if(_texture) {
		SDL_RenderCopy(renderer, _texture, &_src, &_size);
		if(!_isImgBut && _isHovered) {
			SDL_RenderCopy(renderer, _arrow, nullptr, &_arrowRect);
		}
	}
}

void OFSGuiButton::_clickedOnAction() {}