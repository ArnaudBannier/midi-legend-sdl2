/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/title/title_scene.h"

TitleScene *TitleScene_create(SDL_Renderer *renderer)
{
    TitleScene *self = (TitleScene *)calloc(1, sizeof(TitleScene));
    AssertNew(self);

    self->renderer = renderer;

    self->assets = AssetManager_create(renderer);
    self->input = Input_create(true);
    self->canvas = TitleCanvas_create(self);

    self->config.keyCount = 3;
    self->config.musicID = 0;
    self->config.piano = true;

    return self;
}

void TitleScene_destroy(TitleScene *self)
{
    if (!self) return;

    Mix_HaltChannel(0);

    AssetManager_destroy(self->assets);
    TitleCanvas_destroy(self->canvas);
    Input_destroy(self->input);

    free(self);
}

bool TitleScene_update(TitleScene *self)
{
    TitleCanvas *canvas = self->canvas;
    Input *input = self->input;

    // Met à jour les entrées utilisateur
    Input_update(input);
    bool quit = TitleCanvas_update(canvas);

    return quit || self->input->quitPressed;
}

void TitleScene_render(TitleScene *self)
{
    SDL_Renderer *renderer = TitleScene_getRenderer(self);
    AssetManager *assets = TitleScene_getAssetManager(self);

    // Affichage du fond
    SDL_RenderCopy(renderer, assets->textures.background, NULL, NULL);

    // Affichage du canvas
    TitleCanvas_render(self->canvas);
}
