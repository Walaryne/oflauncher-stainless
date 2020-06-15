//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUI_H
#define OFLAUNCHER_STAINLESS_OFSGUI_H

#include "SDL2/SDL.h"
#include <memory>
#include <string>
#include <vector>

class OFSGuiImage {
private:
	SDL_Texture *texture;
	bool ok;

public:
	OFSGuiImage(std::string image_file, SDL_Renderer *renderer);
	~OFSGuiImage();
	bool isOk();
	SDL_Texture *getTexture();
	void renderCopy(SDL_Renderer *renderer);
};

class OFSGui {
private:
	SDL_Window *window;
	SDL_Surface *surface; // depricated because of renderer.  maybe delete later
						  // if its seriously not needed
	SDL_Renderer *renderer;
	std::vector<std::unique_ptr<OFSGuiImage>> imgs;
	bool ok;
	std::string err{};
	bool e_quit;

	void setError(const std::string &err_msg_pre);

public:
	OFSGui();
	~OFSGui();
	bool isOk();
	std::string getError();

	bool loop();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUI_H
