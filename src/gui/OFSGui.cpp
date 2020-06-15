//
// Created by walaryne on 6/14/20.
//

#include "OFSGui.h"

OFSGuiImage::OFSGuiImage(std::string image_file, SDL_Renderer *renderer) {
	ok = true;
	SDL_Surface *textureSurface = SDL_LoadBMP(image_file.c_str());
	if(textureSurface == nullptr) {
		ok = false;
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
		if(texture == nullptr) {
			ok = false;
		}
		SDL_FreeSurface(textureSurface);
	}
}

OFSGuiImage::~OFSGuiImage() { SDL_DestroyTexture(texture); }

bool OFSGuiImage::isOk() { return ok; }

void OFSGuiImage::renderCopy(SDL_Renderer *renderer) {
	// TODO: Later edit the null params to scale and position the texture.
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

OFSGui::OFSGui() {
	e_quit = false;
	ok = true;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		setError("Error initializing SDL: ");
	} else {
		window = SDL_CreateWindow(
			"Open Fortress Launcher", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_SHOWN);
		if(!window) {
			setError("Error initializing SDL window: ");
		} else {
			surface = SDL_GetWindowSurface(window); // depricated
			renderer = SDL_CreateRenderer(window, -1,
										  SDL_RENDERER_ACCELERATED |
											  SDL_RENDERER_PRESENTVSYNC);
			if(renderer == nullptr) {
				setError("Could not initialize Renderer: ");
			} else
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
		}
	}
	if(isOk()) {
		// TODO: eventually have a way to automatically load in all needed
		// images
		imgs.push_back(
			std::make_unique<OFSGuiImage>("../res/bg.bmp", renderer));
	}
	for(auto &x : imgs) {
		ok &= x->isOk();
	}
	if(!isOk())
		setError("Error loading resources: ");
}

OFSGui::~OFSGui() {
	imgs.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void OFSGui::setError(const std::string &err_msg_pre) {
	ok = false;
	err = err_msg_pre + std::string(SDL_GetError());
}

bool OFSGui::isOk() { return ok; }

std::string OFSGui::getError() { return err; }

bool OFSGui::loop() {
	SDL_Event e;

	SDL_UpdateWindowSurface(window); // depricated.  delete later if need to

	SDL_RenderClear(renderer);
	for(auto &i : imgs) {
		i->renderCopy(renderer);
	}
	SDL_RenderPresent(renderer);

	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			e_quit = true;
			break;
		}
	}
	return !e_quit;
}