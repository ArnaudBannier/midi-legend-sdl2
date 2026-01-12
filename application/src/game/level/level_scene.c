/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/level/level_scene.h"

LevelScene *LevelScene_create(
    SDL_Renderer *renderer, int musicID,
    int keyCount, bool pianoMode)
{
    LevelScene *self = (LevelScene *)calloc(1, sizeof(LevelScene));
    AssertNew(self);

    self->renderer = renderer;
    self->assets = AssetManager_create(renderer);
    self->input = Input_create(pianoMode);
    self->track = Track_create(self, g_musics[musicID].textPath);
    self->trackTime = -2.0f;
    self->music = Mix_LoadWAV(g_musics[musicID].musicPath);
    self->canvas = LevelCanvas_create(self);

    self->score.points = 0.0f;

    Track_clearChords(self->track);
    Track_placeNotes(self->track, keyCount);

    return self;
}

void LevelScene_destroy(LevelScene *self)
{
    if (!self) return;

    Mix_HaltChannel(0);
    Mix_FreeChunk(self->music);

    AssetManager_destroy(self->assets);
    Input_destroy(self->input);
    Track_destroy(self->track);
    LevelCanvas_destroy(self->canvas);

    free(self);
}

void LevelScene_start(LevelScene *self)
{
    self->trackTime = -2.0f;
    self->playing = false;
}


bool LevelScene_update(LevelScene *self)
{
    // Met à jour les entrées utilisateur
    Input_update(self->input);

    self->trackTime += Timer_getDelta(g_time);

    if (self->playing == false && self->trackTime >= 0.0)
    {
        int exitStatus = Mix_PlayChannel(0, self->music, 0);
        if (exitStatus < 0)
        {
            assert(false);
        }

        self->playing = true;
        self->trackTime = 0.0;
    }

    Track_update(self->track);

    LevelCanvas_update(self->canvas);

    bool quit = self->input->quitPressed || self->input->menuPressed;
    quit = quit || (self->trackTime > self->track->duration + 2.0f);

    return quit;
}

void LevelScene_render(LevelScene *self)
{
    // Affichage du fond
    SDL_Renderer *renderer = LevelScene_getRenderer(self);
    AssetManager *assets = LevelScene_getAssetManager(self);
    SDL_RenderCopy(renderer, assets->textures.background, NULL, NULL);

    Track_render(self->track);

    SDL_RenderCopy(renderer, assets->textures.logo, NULL, &(g_levelRects.logo));

    //* DEBUG
    // Gizmos de la scène en cyan
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &(g_levelRects.logo));
    //*/

    LevelCanvas_render(self->canvas);
}
