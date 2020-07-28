#ifndef OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
#define OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H

#include "SDL2/SDL.h"
#include <string>
#include <memory>

#include "OFSGuiActs.h"
#include "OFSGuiError.h"
#include "res/EmbedData.h"

#ifdef INCLUDE_RESOURCES
#define resData const EmbedData
#else
#define resData const std::string &
#endif

struct OFSImageData {
	SDL_Texture* tex;
	SDL_Rect src;
	SDL_Rect size;
};

class OFSGuiImage {
protected:
	SDL_Texture *_texture;
	SDL_Renderer * _renderer;
	SDL_Rect _src;
	SDL_Rect _size;
	int _subImages;

	SDL_Texture* _loadSecondImg(resData dataToLoad,
											 SDL_Rect *srcRect,
											 SDL_Rect *sizeRect);

public:
	OFSGuiImage(){};
	OFSGuiImage(resData data, SDL_Renderer *renderer, const int &x,
				const int &y, const int &NumOfSubImages);
	~OFSGuiImage();
	SDL_Texture *getTexture();
	virtual void renderCopy(SDL_Renderer *renderer);
	void setIndex(const int &i);
	virtual GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);
	virtual void setProgress(const float &progress);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
