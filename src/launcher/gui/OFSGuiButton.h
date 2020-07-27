#ifndef OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
#define OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiImage.h"
#include "res/EmbedData.h"

enum ButtonTypes {
	DEFAULT_BUTTON,
	BIG_BOY_BUTTON
};

class OFSGuiButton : public OFSGuiImage {
private:
	OFSImageData _left;
	OFSImageData _mid;
	OFSImageData _right;
	OFSImageData _text;
	GuiActs _act;
	bool _isClicked;
	void _finishLoading();

public:
	OFSGuiButton(SDL_Renderer *renderer, GuiActs actToLink = NOT_CLICKED,
				 const int &x = 0, const int &y = 0, const std::string &text = "", const ButtonTypes& buttonType = DEFAULT_BUTTON);
	~OFSGuiButton();
	void getClickedDown();
	GuiActs getClickedUp();
	void getHover();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
