#ifndef OFLAUNCHER_STAINLESS_OFSGUIELEMENT_H
#define OFLAUNCHER_STAINLESS_OFSGUIELEMENT_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiError.h"
#include "res/EmbedData.h"
#include <memory>

#ifdef INCLUDE_RESOURCES
#define resData const EmbedData
#else
#define resData const std::string &
#endif

class OFSGuiElement {
public:
	OFSGuiElement();
	// OFSGuiElement(const int &x, const int &y, const int &w, const int &h);
	virtual ~OFSGuiElement();

	virtual void render(SDL_Renderer *renderer);
	virtual void onEvent(std::shared_ptr<GuiEvent> e);

	SDL_Rect _size;
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIELEMENT_H
