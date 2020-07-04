#ifndef OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
#define OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiImage.h"
#include "res/EmbedData.h"

class OFSGuiButton : public OFSGuiImage {
private:
	GuiActs _act;
	bool _isClicked;
	void _finishLoading();

public:
	OFSGuiButton(resData data, SDL_Renderer *renderer, GuiActs actToLink,
				 const int &x, const int &y, const int &NumOfSubImages);
	~OFSGuiButton();
	void getClickedDown();
	GuiActs getClickedUp();
	void getHover();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
