/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"

INLINE float Float_clamp(float x, float a, float b)
{
    return fmaxf(a, fminf(b, x));
}

INLINE float Float_clamp01(float x)
{
    return Float_clamp(x, 0.0f, 1.0f);
}

INLINE int Int_clamp(int x, int a, int b)
{
    x = (x < a) ? a : x;
    x = (x > b) ? b : x;
    return x;
}

void SDL_Rect_set(SDL_Rect *rect, int x, int y, int w, int h);
void SDL_FRect_set(SDL_FRect *rect, float x, float y, float w, float h);
