//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUI_H
#define OFLAUNCHER_STAINLESS_OFSGUI_H

#include "SDL2/SDL.h"
#include <string>

class OFSGui {
    private:
        SDL_Window* w;
        SDL_Surface* s;
        bool k;
    public:
        OFSGui();
        bool isOk();
        std::string getError();

};


#endif //OFLAUNCHER_STAINLESS_OFSGUI_H
