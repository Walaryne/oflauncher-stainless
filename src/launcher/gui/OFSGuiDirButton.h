//
// Created by fenteale on 8/2/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUIDIRBUTTON_H
#define OFLAUNCHER_STAINLESS_OFSGUIDIRBUTTON_H

#include "OFSGuiButton.h"
#include "../../nativefiledialog/include/nfd.h"

class OFSGuiDirButton : public OFSGuiButton {
public:
	OFSGuiDirButton(const std::string &name, resData imgData, SDL_Renderer *renderer,
					const int &x = 0, const int &y = 0, const ButtonTypes& buttonType = DEFAULT_BUTTON);

	GuiActs parseEvents(std::shared_ptr<OFSGuiEvent> ev);
};

#endif // OFLAUNCHER_STAINLESS_OFSGUIDIRBUTTON_H
