#ifndef OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
#define OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiElement.h"
#include "OFSGuiError.h"
#include "res/EmbedData.h"


class OFSGuiImage : public OFSGuiElement {
protected:
	SDL_Texture *_texture;
	SDL_Rect _src;
	int _subImages;

public:
	OFSGuiImage(){};
	OFSGuiImage(resData data, SDL_Renderer *renderer, const int &x,
				const int &y, const int &NumOfSubImages);
	~OFSGuiImage();

	void setIndex(const int &i);

	void render(SDL_Renderer *renderer);
	void onEvent(std::shared_ptr<GuiEvent> e);

	SDL_Rect _size;
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIIMAGE_H
