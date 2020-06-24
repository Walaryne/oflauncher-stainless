#ifndef OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H
#define OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H

#include "SDL2/SDL.h"
#include <string>

#include "OFSGuiActs.h"
#include "OFSGuiImage.h"

class OFSGuiButton : public OFSGuiImage {
private:
	GuiActs act;
	bool isClicked;

public:
	OFSGuiButton(const std::string &image_file, SDL_Renderer *renderer,
				 GuiActs actToLink, const int &x, const int &y,
				 const int &NumOfSubImages);
	~OFSGuiButton();
	void getClickedDown();
	GuiActs getClickedUp();
	void getHover();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIBUTTON_H