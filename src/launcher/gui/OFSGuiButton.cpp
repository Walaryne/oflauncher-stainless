#include "OFSGuiButton.h"

#ifdef INCLUDE_RESOURCES
#include "res/button_d.bmp.h"
#define BUTDATA(res_name) & res_name##_bmp_data
#else
#define BUTDATA(res_name) "../res/" #res_name ".bmp"
#endif

#define TEXT_BUMP_VERT 2
#define TEXT_BUMP_HOR  2

static void blitSprite(SDL_Surface* src, SDL_Surface* dst, const int &fullHeight, const int &spriteSize, const int &init_x_src, const int &init_y_src
					   ,const int &init_x_dst, const int &init_y_dst) {
	SDL_Rect cutter, paster;
	cutter.w = spriteSize;
	paster.w = spriteSize;
	cutter.h = spriteSize;
	paster.h = spriteSize;
	//cut top left
	cutter.x = init_x_src;
	cutter.y = init_y_src;
	paster.x = init_x_dst;
	paster.y = init_y_dst;

	SDL_BlitSurface(src, &cutter, dst, &paster); //normal top left
	cutter.y += spriteSize;
	paster.y += fullHeight;
	SDL_BlitSurface(src, &cutter, dst, &paster); //hover top left
	cutter.y += spriteSize;
	paster.y += fullHeight;
	SDL_BlitSurface(src, &cutter, dst, &paster); //selected top left
}


//###### OFSGuiButton ###########
OFSGuiButton::OFSGuiButton(const std::string &name, resData fontData, SDL_Renderer *renderer, GuiActs actToLink,
						   const int &x, const int &y, const std::string &text, const ButtonTypes& buttonType)
	: OFSGuiImage() {
	bool white;
	int textSize;
	int textTopOffset = 0;  //the bigger the button, the more space it looks like there is empty on the bottom.
#ifdef INCLUDE_RESOURCES
	resData *spriteMapData;
#else
	std::string spriteMapData;
#endif

	switch(buttonType){
	case(BIG_BOY_BUTTON):
		spriteMapData = BUTDATA(button_d);
		white = true;
		textSize = 80;
		textTopOffset = 10;
		break;
	case(SMALL_BUTTON):
		spriteMapData = BUTDATA(button_d);
		white = true;
		textSize = 20;
		break;
	default:
		spriteMapData = BUTDATA(button_d);
		white = true;
		textSize = 40;
		break;
	}
#ifdef INCLUDE_RESOURCES
	SDL_RWops *data = SDL_RWFromMem((void *)(fontData.buf),
									fontData.len);
	TTF_Font *font = TTF_OpenFontRW(data, 1, textSize);
	SDL_RWops *rw = SDL_RWFromMem((void *)(spriteMapData->buf), spriteMapData->len);
	SDL_Surface *spriteSurface = SDL_LoadBMP_RW(rw, 1);
#else
	fs::path p = fs::current_path();
	p += "/" + spriteMapData;
	fs::path p2 = fs::current_path();
	p2 += "/" + fontData;
	TTF_Font *font =
		TTF_OpenFont(p2.make_preferred().string().c_str(), textSize);
	SDL_Surface *spriteSurface = SDL_LoadBMP(p.make_preferred().string().c_str());
#endif
	if(font == nullptr)
		throw SDLTTFException("OFSGuiButton");
	if(spriteSurface == nullptr)
		throw SDLException("OFSGuiButton");

	SDL_Color fontcolor;
	if(white)
		fontcolor = {255, 255, 255, 255};
	else
		fontcolor = {0, 0, 0, 255};

	_subImages = 2;
	int w, h;
	SDL_Surface *textSurfaceNoCrop =
		TTF_RenderText_Blended(font, text.c_str(), fontcolor);
	SDL_Surface *textSurface = SDL_CreateRGBSurfaceWithFormat(0, textSurfaceNoCrop->w, textSurfaceNoCrop->h / 1.5, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_Rect textCrop;
	textCrop.x = 0;
	textCrop.y = (textSurfaceNoCrop->h / 4) - textTopOffset;
	textCrop.w = textSurfaceNoCrop->w;
	textCrop.h = textSurfaceNoCrop->h / 1.5;
	SDL_BlitSurface(textSurfaceNoCrop, &textCrop, textSurface, nullptr);
	SDL_FreeSurface(textSurfaceNoCrop);
	if(textSurface == nullptr)
		throw SDLTTFException("OFSGuiText");

	//time to construct our texture
	int spriteSize = (spriteSurface->w - 2) / 4;
	int fullWidth = (spriteSize * 2) + textSurface->w;
	int fullHeight = (spriteSize * 2 ) + (textSurface->h); ///2);
	SDL_Surface* textureSurface = SDL_CreateRGBSurfaceWithFormat(0, fullWidth, fullHeight * 3, 32, SDL_PIXELFORMAT_RGBA32);
	SDL_SetSurfaceAlphaMod(textureSurface, 0xff);

	blitSprite(spriteSurface, textureSurface, fullHeight, spriteSize, 0, 0, 0, 0); //top left
	blitSprite(spriteSurface, textureSurface, fullHeight, spriteSize, spriteSize, 0, fullWidth - spriteSize, 0); //top right
	blitSprite(spriteSurface, textureSurface, fullHeight, spriteSize, spriteSize * 2, 0, 0, fullHeight - spriteSize); //bottom left
	blitSprite(spriteSurface, textureSurface, fullHeight, spriteSize, spriteSize * 3, 0, fullWidth - spriteSize, fullHeight - spriteSize); //bottom right

	SDL_Rect cut, paste;
	//top edge
	for(int xpos = spriteSize; xpos < fullWidth - spriteSize; xpos++)
	{
		cut.w = 1;
		paste.w = 1;
		cut.h = spriteSize;
		paste.h = spriteSize;
		cut.x = (spriteSize*4) + 1;
		cut.y = 0;
		paste.y = 0;
		paste.x = xpos;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += spriteSize;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += spriteSize;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);

	}
	//bottom edge
	for(int xpos = spriteSize; xpos < fullWidth - spriteSize; xpos++)
	{
		cut.w = 1;
		paste.w = 1;
		cut.h = spriteSize;
		paste.h = spriteSize;
		cut.x = (spriteSize*4);
		cut.y = 0;
		paste.y = fullHeight - spriteSize;
		paste.x = xpos;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += spriteSize;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += spriteSize;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);

	}
	//left edge
	for(int ypos = spriteSize; ypos < fullHeight - spriteSize; ypos++)
	{
		cut.w = spriteSize;
		paste.w = spriteSize;
		cut.h = 1;
		paste.h = 1;
		cut.x = 0;
		cut.y = spriteSize * 3;
		paste.y = ypos;
		paste.x = 0;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += 1;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += 1;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
	}
	//right edge
	for(int ypos = spriteSize; ypos < fullHeight - spriteSize; ypos++)
	{
		cut.w = spriteSize;
		paste.w = spriteSize;
		cut.h = 1;
		paste.h = 1;
		cut.x = spriteSize;
		cut.y = spriteSize * 3;
		paste.y = ypos;
		paste.x = fullWidth - spriteSize;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += 1;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
		cut.y += 1;
		paste.y += fullHeight;
		SDL_BlitSurface(spriteSurface, &cut, textureSurface, &paste);
	}

	//get background color
	Uint8 bk_r, bk_g, bk_b, bk_a;
	Uint8 *pix = (Uint8 *)spriteSurface->pixels + (spriteSurface->h -1) * spriteSurface->pitch + (spriteSurface->w -1) * 4;
	SDL_GetRGBA(*(Uint32 *)pix, spriteSurface->format, &bk_r, &bk_g, &bk_b, &bk_a);
	SDL_Rect backing;
	backing.x = spriteSize;
	backing.y = spriteSize;
	backing.w = textSurface->w;
	backing.h = textSurface->h;
	SDL_FillRect(textureSurface, &backing, SDL_MapRGBA(textureSurface->format, bk_r, bk_g, bk_b, bk_a)); //normal
	backing.y += fullHeight;
	pix = (Uint8 *)spriteSurface->pixels + (spriteSurface->h -1) * spriteSurface->pitch + (spriteSurface->w -2) * 4;
	SDL_GetRGBA(*(Uint32 *)pix, spriteSurface->format, &bk_r, &bk_g, &bk_b, &bk_a);
	SDL_FillRect(textureSurface, &backing, SDL_MapRGBA(textureSurface->format, bk_r, bk_g, bk_b, bk_a)); //highlight
	backing.y += fullHeight;
	pix = (Uint8 *)spriteSurface->pixels + (spriteSurface->h -1) * spriteSurface->pitch + (spriteSurface->w -3) * 4;
	SDL_GetRGBA(*(Uint32 *)pix, spriteSurface->format, &bk_r, &bk_g, &bk_b, &bk_a);
	SDL_FillRect(textureSurface, &backing, SDL_MapRGBA(textureSurface->format, bk_r, bk_g, bk_b, bk_a)); //clicked


	SDL_Rect textRect;
	textRect.x = spriteSize;
	textRect.y = spriteSize;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);
	textRect.y += fullHeight;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);
	textRect.y += fullHeight + TEXT_BUMP_VERT;
	textRect.x += TEXT_BUMP_HOR;
	SDL_BlitSurface(textSurface, nullptr, textureSurface, &textRect);
	//ok, make the texture now
	_texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if(_texture == nullptr)
		throw SDLException("OFSGuiText");

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
	SDL_FreeSurface(spriteSurface);


	_act = actToLink;
	_isClicked = false;
	_name = name;
}

OFSGuiButton::~OFSGuiButton() {
}

GuiActs OFSGuiButton::parseEvents(std::shared_ptr<OFSGuiEvent> ev) {
	GuiActs ret = NOT_CLICKED;
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
					ret = _act;
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
	return ret;
}