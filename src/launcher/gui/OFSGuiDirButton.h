//
// Created by fenteale on 8/2/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUIDIRBUTTON_H
#define OFLAUNCHER_STAINLESS_OFSGUIDIRBUTTON_H

#include "OFSGuiButton.h"
#include "../nativefiledialog/src/include/nfd.h"

class OFSGuiDirButton : public OFSGuiButton {
private:
	std::string _path;
	void _clickedOnAction() override;
public:
	OFSGuiDirButton(const std::string &name, resData imgData, resData imgDataSel, SDL_Renderer *renderer, GuiActs actToLink,
					const int &x = 0, const int &y = 0, const ButtonTypes& buttonType = DEFAULT_BUTTON);

	OFSGuiEvent getData(GuiActs typeToGet) override;
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIDIRBUTTON_H
