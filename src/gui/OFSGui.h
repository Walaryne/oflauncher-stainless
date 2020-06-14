//
// Created by walaryne on 6/14/20.
//

#ifndef OFLAUNCHER_STAINLESS_OFSGUI_H
#define OFLAUNCHER_STAINLESS_OFSGUI_H

#include "SDL2/SDL.h"

class OFSGui {
    private:
        SDL_Window* w;
        SDL_Surface* s;
    public:
        void init();

};


#endif //OFLAUNCHER_STAINLESS_OFSGUI_H
