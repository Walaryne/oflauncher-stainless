//
// Created by walaryne on 6/14/20.
//

#include "OFSGui.h"
#include <iostream>

OFSGui::OFSGui() {
	e_quit = false;
	k = true;
	er = "";

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		setError("Error initializing SDL: ");
	} else {
		w = SDL_CreateWindow("Open Fortress Launcher", SDL_WINDOWPOS_UNDEFINED,
							 SDL_WINDOWPOS_UNDEFINED, 640, 480,
							 SDL_WINDOW_SHOWN);
		if(w == nullptr) {
			setError("Error initializing SDL window: ");
		} else {
			s = SDL_GetWindowSurface(w);
		}
	}
}

OFSGui::~OFSGui() {
	// TODO: Clean up all the surfaces and textures loaded here
	SDL_DestroyWindow(w);
	SDL_Quit();
}

void OFSGui::setError(std::string err_msg_pre) {
	k = false;
	er = err_msg_pre = SDL_GetError();
}

bool OFSGui::isOk() { return k; }

std::string OFSGui::getError() { return er; }

bool OFSGui::loop() {
	SDL_Event e;

	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0xFF, 0x00, 0xFF));

	SDL_UpdateWindowSurface(w);

	while(SDL_PollEvent(&e) != 0) {
		switch(e.type) {
		case SDL_QUIT:
			e_quit = true;
			break;
		}
	}
	return !e_quit;
}