#ifndef OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H
#define OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

#include "OFSGuiText.h"

class OFSGuiTextEntry : public OFSGuiText {
private:
	SDL_Texture *_backing;
	SDL_Rect _backSize;

	std::string _text;
	bool _focused;

public:
	OFSGuiTextEntry(resData fontData, SDL_Renderer *renderer, const std::string &text,
					const int &x, const int &y, const int &width, const bool &startFocused = false);
	~OFSGuiTextEntry();

	GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);

	void renderCopy(SDL_Renderer *renderer);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H