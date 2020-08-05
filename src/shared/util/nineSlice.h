//
// Created by Digit on 8/4/2020.
//

#include <SDL2/SDL.h>

// Params for how the nineslice is laid out
// These could probably be passed in per image
#define TOP_BORDER_INSET 32
#define BOTTOM_BORDER_INSET 32
#define LEFT_BORDER_INSET 32
#define RIGHT_BORDER_INSET 32

extern void blitNineSliceToSurface(SDL_Surface *src, SDL_Surface *surface, int width, int height);