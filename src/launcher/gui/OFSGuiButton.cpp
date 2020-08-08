#include "OFSGuiButton.h"

#ifdef INCLUDE_RESOURCES
//#include "res/button_d.bmp.h"
#include "res/button_idle.bmp.h"
#include "res/button_hover.bmp.h"
#include "res/button_press.bmp.h"
#include "res/primary_idle.bmp.h"
#include "res/primary_hover.bmp.h"
#include "res/primary_press.bmp.h"
#define BUTDATA(res_name) & res_name##_bmp_data
#else
#define BUTDATA(res_name) "../res/" #res_name ".bmp"
#endif

#define TEXT_BUMP_VERT 2
#define TEXT_BUMP_HOR  2
#define DROP_SHADOW_DISTANCE 2


//###### OFSGuiButton ###########
OFSGuiButton::OFSGuiButton(const std::string &name, resData fontData, SDL_Renderer *renderer, GuiActs actToLink,
						   const int &x, const int &y, const std::string &text, const ButtonTypes& buttonType)
	: OFSGuiImage() {
	bool white, crop, shadow;
	int textSize;
	int textTopOffset = 0; // the bigger the button, the more space it looks like there is empty on the bottom.
#ifdef INCLUDE_RESOURCES
	resData *spriteMapData_d;
	resData *spriteMapData_h;
	resData *spriteMapData_c;
#else
	std::string spriteMapData_d;
	std::string spriteMapData_h;
	std::string spriteMapData_c;
#endif

	switch(buttonType) {
	case(BIG_BOY_BUTTON):
		spriteMapData_d = BUTDATA(primary_idle);
		spriteMapData_h = BUTDATA(primary_hover);
		spriteMapData_c = BUTDATA(primary_press);
		white = true;
		crop = false;
		shadow = true;
		textSize = 80;
		textTopOffset = 7;
		break;
	case(SMALL_BUTTON):
		spriteMapData_d = BUTDATA(button_idle);
		spriteMapData_h = BUTDATA(button_hover);
		spriteMapData_c = BUTDATA(button_press);
		white = true;
		crop = true;
		shadow = true;
		textSize = 20;
		break;
	default:
		spriteMapData_d = BUTDATA(button_idle);
		spriteMapData_h = BUTDATA(button_hover);
		spriteMapData_c = BUTDATA(button_press);
		crop = false;
		white = true;
		shadow = true;
		textSize = 40;
		break;
	}
#ifdef INCLUDE_RESOURCES
	SDL_RWops *data = SDL_RWFromMem((void *)(fontData.buf), fontData.len);
	TTF_Font *font = TTF_OpenFontRW(data, 1, textSize);
	SDL_RWops *rw =
		SDL_RWFromMem((void *)(spriteMapData_d->buf), spriteMapData_d->len);
	SDL_Surface *spriteSurface_d = SDL_LoadBMP_RW(rw, 1);
	rw = SDL_RWFromMem((void *)(spriteMapData_h->buf), spriteMapData_h->len);
	SDL_Surface *spriteSurface_h = SDL_LoadBMP_RW(rw, 1);
	rw = SDL_RWFromMem((void *)(spriteMapData_c->buf), spriteMapData_c->len);
	SDL_Surface *spriteSurface_c = SDL_LoadBMP_RW(rw, 1);
#else
	fs::path p_d = fs::current_path();
	p_d += "/" + spriteMapData_d;
	fs::path p_h = fs::current_path();
	p_h += "/" + spriteMapData_h;
	fs::path p_c = fs::current_path();
	p_c += "/" + spriteMapData_c;
	fs::path p2 = fs::current_path();
	p2 += "/" + fontData;
	TTF_Font *font =
		TTF_OpenFont(p2.make_preferred().string().c_str(), textSize);
	SDL_Surface *spriteSurface_d =
		SDL_LoadBMP(p_d.make_preferred().string().c_str());
	SDL_Surface *spriteSurface_h =
		SDL_LoadBMP(p_h.make_preferred().string().c_str());
	SDL_Surface *spriteSurface_c =
		SDL_LoadBMP(p_c.make_preferred().string().c_str());
#endif
	if(font == nullptr)
		throw SDLTTFException("OFSGuiButton");

	SDL_Color fontcolor;
	if(white)
		fontcolor = {255, 255, 255, 255};
	else
		fontcolor = {0, 0, 0, 255};

	SDL_Surface *textSurface = nullptr;

	if(crop) {

		SDL_Surface *textSurfaceNoCrop =
			TTF_RenderText_Blended(font, text.c_str(), fontcolor);
		textSurface = SDL_CreateRGBSurfaceWithFormat(
			0, textSurfaceNoCrop->w + (shadow * DROP_SHADOW_DISTANCE), textSurfaceNoCrop->h / 1.5, 32,
			SDL_PIXELFORMAT_RGBA32);
		SDL_Rect textCrop;
		textCrop.x = 0;
		textCrop.y = (textSurfaceNoCrop->h / 4) - textTopOffset;
		textCrop.w = textSurfaceNoCrop->w;
		textCrop.h = textSurfaceNoCrop->h / 1.5;
		if(shadow){
			SDL_Surface *dropShadow = TTF_RenderText_Blended(font, text.c_str(), {0, 0, 0, 250});
			SDL_Rect dropDst = {DROP_SHADOW_DISTANCE, textTopOffset + DROP_SHADOW_DISTANCE, dropShadow->w, dropShadow->h};
			SDL_BlitSurface(dropShadow, &textCrop, textSurface, &dropDst);
			SDL_FreeSurface(dropShadow);
		}

		SDL_BlitSurface(textSurfaceNoCrop, &textCrop, textSurface, nullptr);
		SDL_FreeSurface(textSurfaceNoCrop);
	}
	else {
		SDL_Surface *textSurfaceNoCrop =
			TTF_RenderText_Blended(font, text.c_str(), fontcolor);
		textSurface = SDL_CreateRGBSurfaceWithFormat(
			0, textSurfaceNoCrop->w, textSurfaceNoCrop->h, 32,
			SDL_PIXELFORMAT_RGBA32);
		SDL_Rect textCrop;
		textCrop.x = 0;
		textCrop.y = textTopOffset;
		textCrop.w = textSurfaceNoCrop->w;
		textCrop.h = textSurfaceNoCrop->h;
		if(shadow){
			SDL_Surface *dropShadow = TTF_RenderText_Blended(font, text.c_str(), {0, 0, 0, 250});
			SDL_Rect dropDst = {DROP_SHADOW_DISTANCE, textTopOffset + DROP_SHADOW_DISTANCE, dropShadow->w, dropShadow->h};
			SDL_BlitSurface(dropShadow, nullptr, textSurface, &dropDst);
			SDL_FreeSurface(dropShadow);
		}
		SDL_BlitSurface(textSurfaceNoCrop, nullptr, textSurface, &textCrop);
		SDL_FreeSurface(textSurfaceNoCrop);
	}

	if(textSurface == nullptr)
		throw SDLTTFException("OFSGuiText");



	_renderer = renderer;
	_act = actToLink;
	_name = name;

	_finishLoading(spriteSurface_d, spriteSurface_h, spriteSurface_c, textSurface, x, y, shadow);
}

OFSGuiButton::OFSGuiButton(const std::string &name, const EmbedData imgData, SDL_Renderer *renderer, GuiActs actToLink, const int &x, const int &y, const ButtonTypes &buttonType)
	: OFSGuiImage() {
#ifdef INCLUDE_RESOURCES
	resData *spriteMapData_d;
	resData *spriteMapData_h;
	resData *spriteMapData_c;
#else
	std::string spriteMapData_d;
	std::string spriteMapData_h;
	std::string spriteMapData_c;
#endif

	switch(buttonType) {
	case(BIG_BOY_BUTTON):
		spriteMapData_d = BUTDATA(primary_idle);
		spriteMapData_h = BUTDATA(primary_hover);
		spriteMapData_c = BUTDATA(primary_press);
		break;
	case(SMALL_BUTTON):
		spriteMapData_d = BUTDATA(button_idle);
		spriteMapData_h = BUTDATA(button_hover);
		spriteMapData_c = BUTDATA(button_press);
		break;
	default:
		spriteMapData_d = BUTDATA(button_idle);
		spriteMapData_h = BUTDATA(button_hover);
		spriteMapData_c = BUTDATA(button_press);
		break;
	}
#ifdef INCLUDE_RESOURCES
	SDL_RWops *data = SDL_RWFromMem((void *)(imgData.buf), imgData.len);
	SDL_Surface *textSurface = SDL_LoadBMP_RW(data, 1);
	SDL_RWops *rw =
		SDL_RWFromMem((void *)(spriteMapData_d->buf), spriteMapData_d->len);
	SDL_Surface *spriteSurface_d = SDL_LoadBMP_RW(rw, 1);
	rw = SDL_RWFromMem((void *)(spriteMapData_h->buf), spriteMapData_h->len);
	SDL_Surface *spriteSurface_h = SDL_LoadBMP_RW(rw, 1);
	rw = SDL_RWFromMem((void *)(spriteMapData_c->buf), spriteMapData_c->len);
	SDL_Surface *spriteSurface_c = SDL_LoadBMP_RW(rw, 1);
#else
	fs::path p_d = fs::current_path();
	p_d += "/" + spriteMapData_d;
	fs::path p_h = fs::current_path();
	p_h += "/" + spriteMapData_h;
	fs::path p_c = fs::current_path();
	p_c += "/" + spriteMapData_c;
	fs::path p2 = fs::current_path();
	p2 += "/" + imgData;
	SDL_Surface* textSurface =
		SDL_LoadBMP(p2.make_preferred().string().c_str());
	SDL_Surface *spriteSurface_d =
		SDL_LoadBMP(p_d.make_preferred().string().c_str());
	SDL_Surface *spriteSurface_h =
		SDL_LoadBMP(p_h.make_preferred().string().c_str());
	SDL_Surface *spriteSurface_c =
		SDL_LoadBMP(p_c.make_preferred().string().c_str());
#endif
	if(textSurface == nullptr)
		throw SDLTTFException("OFSGuiText");

	_renderer = renderer;
	_act = actToLink;
	_name = name;

	_finishLoading(spriteSurface_d, spriteSurface_h, spriteSurface_c, textSurface, x, y, false);
}

void OFSGuiButton::_finishLoading(SDL_Surface *spriteSurface_d, SDL_Surface *spriteSurface_h, SDL_Surface *spriteSurface_c, SDL_Surface *textSurface, const int &x, const int &y, const bool &shadow) {
	int fullWidth = textSurface->w + LEFT_BORDER_INSET + RIGHT_BORDER_INSET;
	int fullHeight = textSurface->h + TOP_BORDER_INSET + BOTTOM_BORDER_INSET;
	SDL_Surface *textureSurface = SDL_CreateRGBSurfaceWithFormat(0, fullWidth, fullHeight * 3, 32, SDL_PIXELFORMAT_RGBA32);

	SDL_Surface *textureSurface_tmp = SDL_CreateRGBSurfaceWithFormat(0, fullWidth, fullHeight, 32, SDL_PIXELFORMAT_RGBA32);
	blitNineSliceToSurface(spriteSurface_d, textureSurface_tmp, fullWidth, fullHeight);
	SDL_Rect paster = {0, 0, fullWidth, fullHeight};
	SDL_BlitSurface(textureSurface_tmp, nullptr, textureSurface, &paster);

	blitNineSliceToSurface(spriteSurface_h, textureSurface_tmp, fullWidth, fullHeight);
	paster.y += fullHeight;
	SDL_BlitSurface(textureSurface_tmp, nullptr, textureSurface, &paster);

	blitNineSliceToSurface(spriteSurface_c, textureSurface_tmp, fullWidth, fullHeight);
	paster.y += fullHeight;
	SDL_BlitSurface(textureSurface_tmp, nullptr, textureSurface, &paster);

	SDL_Rect textRect;
	textRect.x = LEFT_BORDER_INSET;
	textRect.y = TOP_BORDER_INSET;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);

	textRect.y += fullHeight;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);

	textRect.y += fullHeight + TEXT_BUMP_VERT;
	textRect.x += TEXT_BUMP_HOR;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);

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
	SDL_FreeSurface(spriteSurface_d);
	SDL_FreeSurface(spriteSurface_h);
	SDL_FreeSurface(spriteSurface_c);
}

GuiActs OFSGuiButton::parseEvents(std::shared_ptr<OFSGuiEvent> ev) {
	GuiActs ret = NOT_CLICKED;
	if(ev->eventType == EVENT_SDL && (ev->name == _name || ev->name == "all")) {
		SDL_Event* sdle = (SDL_Event*) ev->data;
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
	return ret;
}