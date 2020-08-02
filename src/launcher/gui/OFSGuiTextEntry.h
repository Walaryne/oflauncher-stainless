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
	SDL_Texture *_cursor;
	SDL_Rect _cursorSize;

	std::string _text;
	bool _focused;
	bool _updateTextNow = false;
	Uint32 _toggleCursorTick = 0;
	bool _showCursor = false;

	void _updateText();
public:
	OFSGuiTextEntry(const std::string &name, resData fontData, SDL_Renderer *renderer, const std::string &text,
					const int &x, const int &y, const int &width, const bool &startFocused = false);
	~OFSGuiTextEntry();

	GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);
	void getData(GuiActs typeToGet, void * data);

	void renderCopy(SDL_Renderer *renderer);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUITEXTENTRY_H