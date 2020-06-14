//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUI_H
#define OFLAUNCHER_STAINLESS_OFSGUI_H

#include "SDL2/SDL.h"
#include <string>

class OFSGui {
  private:
	SDL_Window *w;
	SDL_Surface *s;
	SDL_Event e{};
	bool k;
	std::string er;
	bool e_quit;

	void setError(std::string err_msg_pre);

  public:
	OFSGui();
	~OFSGui();
	bool isOk();
	std::string getError();

	bool loop();
};

#endif // OFLAUNCHER_STAINLESS_OFSGUI_H
