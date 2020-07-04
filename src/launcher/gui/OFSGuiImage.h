#ifndef OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
#define OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiError.h"
#include "res/EmbedData.h"

#ifdef INCLUDE_RESOURCES
#define resData const EmbedData
#else
#define resData const std::string &
#endif

class OFSGuiImage {
protected:
	SDL_Texture *_texture;
	SDL_Rect _src;
	SDL_Rect _size;
	int _subImages;

public:
	OFSGuiImage(){};
	OFSGuiImage(resData data, SDL_Renderer *renderer, const int &x,
				const int &y, const int &NumOfSubImages);
	~OFSGuiImage();
	SDL_Texture *getTexture();
	virtual void renderCopy(SDL_Renderer *renderer);
	void setIndex(const int &i);
	virtual void getClickedDown();
	virtual GuiActs getClickedUp();
	virtual void getHover();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
