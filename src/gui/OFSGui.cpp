//
// Created by walaryne on 6/14/20.
//

#include "OFSGui.h"

OFSGui::OFSGui() {
	e_quit = false;
	ok = true;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		setError("Error initializing SDL: ");
	} else {
		window = SDL_CreateWindow("Open Fortress Launcher", SDL_WINDOWPOS_UNDEFINED,
							 SDL_WINDOWPOS_UNDEFINED, 640, 480,
							 SDL_WINDOW_SHOWN);
		if(!window) {
			setError("Error initializing SDL window: ");
		} else {
			surface = SDL_GetWindowSurface(window);
		}
	}
}

OFSGui::~OFSGui() {
	// TODO: Clean up all the surfaces and textures loaded here
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void OFSGui::setError(const std::string& err_msg_pre) {
	ok = false;
	err = err_msg_pre + std::string(SDL_GetError());
}

bool OFSGui::isOk() { return ok; }

std::string OFSGui::getError() { return err; }

bool OFSGui::loop() {
	SDL_Event e;

	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));

	SDL_UpdateWindowSurface(window);

	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			e_quit = true;
			break;
		}
	}
	return !e_quit;
}