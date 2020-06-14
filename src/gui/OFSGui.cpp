//
// Created by walaryne on 6/14/20.
//

#include "OFSGui.h"
#include "SDL2/SDL.h"

void OFSGui::init() {
    int test = SDL_Init( SDL_INIT_VIDEO );

    w = SDL_CreateWindow( "Open Fortress Launcher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );

    s = SDL_GetWindowSurface( w );
    SDL_FillRect( s, NULL, SDL_MapRGB( s-> format, 0xFF, 0x00, 0xFF ) );

    SDL_UpdateWindowSurface( w );
    SDL_Delay( 2000 );
}