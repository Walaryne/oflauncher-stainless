#ifndef OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
#define OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

#include "OFSGuiActs.h"

class OFSGuiImage {
protected:
	SDL_Texture *texture;
	SDL_Rect src;
	SDL_Rect size;
	bool ok;
	int subImages;

public:
	OFSGuiImage(){};
	OFSGuiImage(const std::string &image_file, SDL_Renderer *renderer,
				const int &x, const int &y, const int &NumOfSubImages);
	~OFSGuiImage();
	bool isOk();
	SDL_Texture *getTexture();
	virtual void renderCopy(SDL_Renderer *renderer);
	void setIndex(const int &i);
	virtual void getClickedDown();
	virtual GuiActs getClickedUp();
	virtual void getHover();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H