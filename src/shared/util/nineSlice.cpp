//
// Created by Digit on 8/4/2020.
//

#include "nineSlice.h"



/**
 * Blits a nine-slice sprite sheet into the target surface
 * @param src - source nine-slice sprite sheet
 * @param surface - destination
 * @param width - width of the desired sprite
 * @param height - height of the desired texture
 */
void blitNineSliceToSurface(SDL_Surface *src, SDL_Surface *surface, int width, int height) {
    SDL_SetSurfaceBlendMode(src, SDL_BLENDMODE_NONE);

    // Rects that represent all the slices of the sheet
    SDL_Rect topLeftCorner{};
    topLeftCorner.x = 0;
    topLeftCorner.y = 0;
    topLeftCorner.w = LEFT_BORDER_INSET;
    topLeftCorner.h = TOP_BORDER_INSET;

    SDL_Rect topRightCorner{};
    topRightCorner.x = src->w - RIGHT_BORDER_INSET;
    topRightCorner.y = 0;
    topRightCorner.w = RIGHT_BORDER_INSET;
    topRightCorner.h = TOP_BORDER_INSET;

    SDL_Rect center{};
    center.x = LEFT_BORDER_INSET;
    center.y = TOP_BORDER_INSET;
    center.w = src->w - RIGHT_BORDER_INSET - LEFT_BORDER_INSET;
    center.h = src->h - BOTTOM_BORDER_INSET - TOP_BORDER_INSET;

    SDL_Rect bottomLeftCorner{};
    bottomLeftCorner.x = 0;
    bottomLeftCorner.y =  src->h - BOTTOM_BORDER_INSET;
    bottomLeftCorner.w = LEFT_BORDER_INSET;
    bottomLeftCorner.h = BOTTOM_BORDER_INSET;

    SDL_Rect bottomRightCorner{};
    bottomRightCorner.x = src->w - RIGHT_BORDER_INSET;
    bottomRightCorner.y = src->h - BOTTOM_BORDER_INSET;
    bottomRightCorner.w = RIGHT_BORDER_INSET;
    bottomRightCorner.h = BOTTOM_BORDER_INSET;

    SDL_Rect topBorder{};
    topBorder.x = LEFT_BORDER_INSET;
    topBorder.y = 0;
    topBorder.w = src->w - LEFT_BORDER_INSET - RIGHT_BORDER_INSET;
    topBorder.h = TOP_BORDER_INSET;

    SDL_Rect bottomBorder{};
    bottomBorder.x = LEFT_BORDER_INSET;
    bottomBorder.y = src->h - BOTTOM_BORDER_INSET;
    bottomBorder.w = src->w - LEFT_BORDER_INSET - RIGHT_BORDER_INSET;
    bottomBorder.h = BOTTOM_BORDER_INSET;

    SDL_Rect leftBorder{};
    leftBorder.x = 0;
    leftBorder.y = TOP_BORDER_INSET;
    leftBorder.w = LEFT_BORDER_INSET;
    leftBorder.h = src->h - BOTTOM_BORDER_INSET - TOP_BORDER_INSET;

    SDL_Rect rightBorder{};
    rightBorder.x = src->w - RIGHT_BORDER_INSET;
    rightBorder.y = TOP_BORDER_INSET;
    rightBorder.w = RIGHT_BORDER_INSET;
    rightBorder.h = src->h - BOTTOM_BORDER_INSET - TOP_BORDER_INSET;

    SDL_Rect dst;

    // Draw the center tiled over whole image
    dst.x = 0;
    dst.y = 0;
    dst.w = center.w;
    dst.h = center.h;
    while (dst.y <= height) {
        while (dst.x <= width + center.w) {
            SDL_BlitSurface(src, &center, surface, &dst);
            dst.x += center.w;
        }
        dst.x = 0;
        dst.y += center.h;
    }

    // Draw the left and right borders
    dst.x = 0;
    dst.y = 0;
    dst.w = leftBorder.w;
    dst.h = leftBorder.h;
    while (dst.y <= height) {
        SDL_BlitSurface(src, &leftBorder, surface, &dst);
        dst.y += leftBorder.h;
    }

    dst.x = width - rightBorder.w;
    dst.y = 0;
    dst.w = rightBorder.w;
    dst.h = rightBorder.h;
    while (dst.y <= height) {
        SDL_BlitSurface(src, &rightBorder, surface, &dst);
        dst.y += rightBorder.h;
    }

    // Draw the top and bottom borders
    dst.x = 0;
    dst.y = 0;
    dst.w = topBorder.w;
    dst.h = topBorder.h;
    while (dst.x <= width) {
        SDL_BlitSurface(src, &topBorder, surface, &dst);
        dst.x += topBorder.w;
    }

    dst.x = 0;
    dst.y = height - BOTTOM_BORDER_INSET;
    dst.w = bottomBorder.w;
    dst.h = bottomBorder.h;
    while (dst.x <= width) {
        SDL_BlitSurface(src, &bottomBorder, surface, &dst);
        dst.x += bottomBorder.w;
    }

    // Place the corners, these do not scale
    // Draw Top Left
    dst.x = 0;
    dst.y = 0;
    dst.w = LEFT_BORDER_INSET;
    dst.h = TOP_BORDER_INSET;
    SDL_BlitSurface(src, &topLeftCorner, surface, &dst);

    // Draw Top Right
    dst.x = width - RIGHT_BORDER_INSET;
    dst.y = 0;
    dst.w = RIGHT_BORDER_INSET;
    dst.h = TOP_BORDER_INSET;
    SDL_BlitSurface(src, &topRightCorner, surface, &dst);

    // Draw Bottom Left
    dst.x = 0;
    dst.y = height - BOTTOM_BORDER_INSET;
    dst.w = LEFT_BORDER_INSET;
    dst.h = BOTTOM_BORDER_INSET;
    SDL_BlitSurface(src, &bottomLeftCorner, surface, &dst);

    // Draw Bottom right
    dst.x = width - RIGHT_BORDER_INSET;
    dst.y = height - BOTTOM_BORDER_INSET;
    dst.w = RIGHT_BORDER_INSET;
    dst.h = BOTTOM_BORDER_INSET;
    SDL_BlitSurface(src, &bottomRightCorner, surface, &dst);
}