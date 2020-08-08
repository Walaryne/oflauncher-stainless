#ifndef OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
#define OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiImage.h"
#include "../../shared/util/nineSlice.h"
#include "res/EmbedData.h"

enum ButtonTypes {
	DEFAULT_BUTTON,
	BIG_BOY_BUTTON,
	SMALL_BUTTON
};

class OFSGuiButton : public OFSGuiImage {
private:
	void _finishLoading(SDL_Surface *spriteSurface_d, SDL_Surface *spriteSurface_h, SDL_Surface *spriteSurface_c, SDL_Surface *textSurface, const int &x, const int &y, const bool &shadow);

protected:
	GuiActs _act;
	bool _isClicked;
	virtual void _clickedOnAction();

public:
	OFSGuiButton(const std::string &name, resData fontData, SDL_Renderer *renderer, GuiActs actToLink = NOT_CLICKED,
				 const int &x = 0, const int &y = 0, const std::string &text = "", const ButtonTypes& buttonType = DEFAULT_BUTTON);
	OFSGuiButton(const std::string &name, resData imgData, SDL_Renderer *renderer, GuiActs actToLink = NOT_CLICKED,
				 const int &x = 0, const int &y = 0, const ButtonTypes& buttonType = DEFAULT_BUTTON);
	GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
