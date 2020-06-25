//
// Created by walaryne on 6/14/20.
//

#include "OFSGui.h"
#include <iostream>

//########### OFSGui ############
OFSGui::OFSGui() {
	e_quit = false;
	ok = true;
	bindFuncs.emplace(NOT_CLICKED, nullptr);

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		setError("Error initializing SDL: ");
	} else {
		window =
			SDL_CreateWindow("Open Fortress Launcher", SDL_WINDOWPOS_UNDEFINED,
							 SDL_WINDOWPOS_UNDEFINED, 640, 360,
							 SDL_WINDOW_SHOWN | SDL_WINDOW_UTILITY);
		// On my computer, I have "unredir-if-possible" enabled in my picom
		// config, and this program causes that to trigger unless you have the
		// SDL_WINDOW_UTILIY flag lol
		if(!window) {
			setError("Error initializing SDL window: ");
		} else {
			// surface = SDL_GetWindowSurface(window); // keeping this here to
			// say that this breaks on ubuntu for some reason.  We arent using
			// it anyways.
			renderer = SDL_CreateRenderer(window, -1,
										  SDL_RENDERER_ACCELERATED |
											  SDL_RENDERER_PRESENTVSYNC);
			if(renderer == nullptr) {
				setError("Could not initialize Renderer: ");
			} else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
				if(TTF_Init() == -1)
					setError("TTF error: ", true);
			}
		}
	}
	if(isOk()) {

		setupLayout();

		for(auto &x : imgs) {
			ok &= x->isOk();
		}
		if(!isOk())
			setError("Error loading resources: ");
	}
}

OFSGui::~OFSGui() {
	imgs.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void OFSGui::setError(const std::string &err_msg_pre, const bool &isTTFError) {
	ok = false;
	err = err_msg_pre;
	if(isTTFError)
		err += std::string(TTF_GetError());
	else
		err += std::string(SDL_GetError());
}

bool OFSGui::isOk() {
	return ok;
}

std::string OFSGui::getError() {
	return err;
}

void OFSGui::bindActivity(GuiActs actToBind, GuiButtonFunction funcPoint) {
	bindFuncs.emplace(actToBind, funcPoint);
}
void OFSGui::bindActivity(GuiActs actToBind, GuiButtonMethod funcPoint) {
	bindMeths.emplace(actToBind, funcPoint);
}

bool OFSGui::loop() {
	SDL_Event e;

	// SDL_UpdateWindowSurface(window); // depricated.  delete later if need to

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
		case SDL_MOUSEBUTTONDOWN:
			for(auto &i : imgs) {
				i->getClickedDown();
			}
			break;
		case SDL_MOUSEBUTTONUP:
			for(auto &i : imgs) {
				GuiActs a = i->getClickedUp();

				if(bindFuncs[a])
					bindFuncs[a]();
				else if(bindMeths[a]) {
					bindMeths[a](this);
					break;
				}
			}
			break;
		default:
			for(auto &i : imgs) {
				i->getHover();
			}
			break;
		}
	}
	SDL_PumpEvents();

	return !e_quit;
}

void OFSGui::addImage(const std::string &image_file, const int &x, const int &y,
					  const int &NumOfSubImages) {
	imgs.push_back(std::make_unique<OFSGuiImage>(image_file, renderer, x, y,
												 NumOfSubImages));
}
void OFSGui::addButton(const std::string &image_file, GuiActs actToLink,
					   const int &x = 0, const int &y = 0,
					   const int &NumOfSubImages = 0) {
	imgs.push_back(std::make_unique<OFSGuiButton>(
		image_file, renderer, actToLink, x, y, NumOfSubImages));
}
void OFSGui::addText(const std::string &text, const int &x, const int &y) {
	imgs.push_back(std::make_unique<OFSGuiText>(renderer, text, x, y));
}
void OFSGui::addTextEntry(const std::string &text, const int &x, const int &y,
						  const int &width) {
	imgs.push_back(
		std::make_unique<OFSGuiTextEntry>(renderer, text, x, y, width));
}
void OFSGui::setLastIndex(const int &i) {
	imgs.back()->setIndex(i);
}

void OFSGui::clearLayout() {
	imgs.clear();
	// bindFuncs.clear();
	bindMeths.clear();
}