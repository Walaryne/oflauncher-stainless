//
// Created by walaryne on 6/14/20.
//

#include "OFSGui.h"

OFSGui::OFSGui() {
	k = true;
	er = "";

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		setError("Error initializing SDL: ");
	} else {
		w = SDL_CreateWindow("Open Fortress Launcher", SDL_WINDOWPOS_UNDEFINED,
							 SDL_WINDOWPOS_UNDEFINED, 640, 480,
							 SDL_WINDOW_SHOWN);
		if(w == NULL) {
			setError("Error initializing SDL window: ");
		} else {
			s = SDL_GetWindowSurface(w);
			SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0xFF, 0x00, 0xFF));

			SDL_UpdateWindowSurface(w);
			SDL_Delay(2000);
		}
	}
}

void OFSGui::setError(std::string err_msg_pre) {
	k = false;
	er = err_msg_pre = SDL_GetError();
}

bool OFSGui::isOk() { return k; }

std::string OFSGui::getError() { return er; }