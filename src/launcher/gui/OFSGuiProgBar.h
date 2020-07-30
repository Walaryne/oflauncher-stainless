#ifndef OFLAUNCHER_STAINLESS_OFSGUIPROGBAR_H
#define OFLAUNCHER_STAINLESS_OFSGUIPROGBAR_H

#include "SDL2/SDL.h"

#include "OFSGuiImage.h"

class OFSGuiProgBar : public OFSGuiImage {
private:
	SDL_Texture *_leftcap;
	SDL_Texture *_rightcap;
	SDL_Rect _leftSrc;
	SDL_Rect _leftSize;
	SDL_Rect _rightSrc;
	SDL_Rect _rightSize;
	SDL_Texture *_middleNone;
	SDL_Rect _mnSrc;
	SDL_Rect _mnSize;

	int _barWidth;
	int _xPos;

	int _progress;

	SDL_Renderer *_renderer;

public:
	OFSGuiProgBar(resData data, SDL_Renderer *renderer, const int &x,
				  const int &y, const int &width);
	~OFSGuiProgBar();

	void renderCopy(SDL_Renderer *renderer);

	GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);
};

#endif