/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "utils/math.h"

void SDL_Rect_set(SDL_Rect *rect, int x, int y, int w, int h)
{
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void SDL_FRect_set(SDL_FRect *rect, float x, float y, float w, float h)
{
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}
