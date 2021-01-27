#ifndef OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
#define OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H

#include "SDL2/SDL.h"
#include <string>
#include <memory>

#include "OFSGuiActs.h"
#include "OFSGuiError.h"
#include "res/EmbedData.h"

#define resData const EmbedData


struct OFSImageData {
	SDL_Texture* tex;
	SDL_Rect src;
	SDL_Rect size;
};

class OFSGuiImage {
protected:
	SDL_Texture *_texture;
	SDL_Renderer * _renderer;
	SDL_Rect _src{};
	SDL_Rect _size{};
	int _subImages;
	std::string _name;

	void setIndex(const int &i);

	SDL_Texture* _loadSecondImg(resData dataToLoad,
											 SDL_Rect *srcRect,
											 SDL_Rect *sizeRect);

public:
	OFSGuiImage(){};
	OFSGuiImage(const std::string &name, resData data, SDL_Renderer *renderer, const int &x,
				const int &y, const int &NumOfSubImages);
	~OFSGuiImage();
	virtual std::string getName();
	SDL_Texture *getTexture();
	virtual void renderCopy(SDL_Renderer *renderer);

	virtual GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);
	virtual OFSGuiEvent getData(GuiActs typeToGet);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
