#ifndef OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
#define OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiImage.h"
//#include "../../shared/util/nineSlice.h"
#include "res/EmbedData.h"

enum ButtonTypes {
	DEFAULT_BUTTON,
	BIG_BOY_BUTTON,
	SMALL_BUTTON,
	COMPUTER_BUTTON
};

class OFSGuiButton : public OFSGuiImage {
private:
	void _finishLoading(SDL_Surface *textSurface, SDL_Surface *selectedSurface, const int &x, const int &y, const bool &shadow);

protected:
	GuiActs _act;
	bool _isClicked;
	bool _isHovered;
	virtual void _clickedOnAction();

	bool _isImgBut;
	SDL_Texture* _arrow;
	SDL_Rect _arrowRect;

public:
	OFSGuiButton(const std::string &name, resData fontData, SDL_Renderer *renderer, GuiActs actToLink = NOT_CLICKED,
				 const int &x = 0, const int &y = 0, const std::string &text = "", const int fontSize = 30);
	OFSGuiButton(const std::string &name, resData imgData, resData imgDataSel, SDL_Renderer *renderer, GuiActs actToLink = NOT_CLICKED,
				 const int &x = 0, const int &y = 0, const ButtonTypes& buttonType = DEFAULT_BUTTON);
	GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);
	void renderCopy(SDL_Renderer *renderer);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
