/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "utils/text.h"

void Text_refreshTexture(Text *self);

Text *Text_create(SDL_Renderer *renderer, TTF_Font *fonts, const char *str, SDL_Color color)
{
    Text *self = (Text *)calloc(1, sizeof(Text));
    AssertNew(self);

    self->renderer = renderer;
    self->fonts = fonts;
    self->str = strdup(str);
    self->color = color;
    self->texture = NULL;

    Text_refreshTexture(self);

    return self;
}

void Text_destroy(Text *self)
{
    if (!self) return;

    if (self->texture)
    {
        SDL_DestroyTexture(self->texture);
    }
    free(self->str);
    free(self);
}

void Text_setString(Text *self, const char *str)
{
    if (strcmp(self->str, str) == 0)
    {
        return;
    }

    free(self->str);
    self->str = strdup(str);

    Text_refreshTexture(self);
}

void Text_setColor(Text *self, SDL_Color color)
{
    if (memcmp(&(self->color), &color, sizeof(SDL_Color)) == 0)
    {
        return;
    }

    self->color = color;
    Text_refreshTexture(self);
}

void Text_refreshTexture(Text *self)
{
    assert(self);

    if (self->texture)
    {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
    }

    SDL_Surface *surface = TTF_RenderUTF8_Blended(self->fonts, self->str, self->color);
    AssertNew(surface);
    self->texture = SDL_CreateTextureFromSurface(self->renderer, surface);
    AssertNew(self->texture);

    SDL_FreeSurface(surface);
}

