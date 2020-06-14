//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUI_H
#define OFLAUNCHER_STAINLESS_OFSGUI_H

#include "SDL2/SDL.h"
#include <string>

class OFSGui {
  private:
	SDL_Window *window;
	SDL_Surface *surface;
	bool ok;
	std::string err{};
	bool e_quit;

	void setError(const std::string& err_msg_pre);

  public:
	OFSGui();
	~OFSGui();
	bool isOk();
	std::string getError();

	bool loop();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUI_H
