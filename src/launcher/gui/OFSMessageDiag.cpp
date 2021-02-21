//
// Created by fenteale on 2/19/21.
//

#include "OFSMessageDiag.h"

int OFSYesNoDialog(std::string title, std::string message) {
	SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes"},
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "No"}
	};

	SDL_MessageBoxData askSDK = {
		SDL_MESSAGEBOX_WARNING,
		nullptr,
		title.c_str(),
		message.c_str(),
		SDL_arraysize(buttons),
		buttons,
		nullptr
	};
	int buttonid;
	if(SDL_ShowMessageBox(&askSDK, &buttonid) < 0)
		throw;

	return buttonid;
}