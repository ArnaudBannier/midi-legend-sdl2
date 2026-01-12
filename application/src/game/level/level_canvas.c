/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/level/level_canvas.h"
#include "game/level/level_scene.h"
#include "utils/math.h"

LevelCanvas *LevelCanvas_create(LevelScene *scene)
{
    LevelCanvas *self = (LevelCanvas *)calloc(1, sizeof(LevelCanvas));
    AssertNew(self);

    AssetManager *assets = LevelScene_getAssetManager(scene);
    SDL_Renderer *renderer = LevelScene_getRenderer(scene);

    self->scene = scene;
    self->textPoints = Text_create(renderer, assets->fonts.big, "0", assets->colors.blue);

    return self;
}

void LevelCanvas_destroy(LevelCanvas *self)
{
    if (!self) return;

    Text_destroy(self->textPoints);

    free(self);
}

void LevelCanvas_render(LevelCanvas *self)
{
    LevelScene *scene = self->scene;
    Track *track = LevelScene_getTrack(scene);
    AssetManager *assets = LevelScene_getAssetManager(scene);
    SDL_Renderer *renderer = LevelScene_getRenderer(scene);

    // Rectangle de fond
    SDL_Color color = assets->colors.green;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 60);
    SDL_RenderFillRect(renderer, &(g_levelRects.uiRect));

    int w, h;
    SDL_Rect dst = { 0 };
    SDL_Texture *texture = NULL;

    // Points
    texture = Text_getTexture(self->textPoints);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    dst.x = g_levelRects.points.x + (g_levelRects.points.w - w) / 2;
    dst.y = g_levelRects.points.y - 23;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    // Barre de progression
    dst = g_levelRects.progressBar;
    color = assets->colors.black;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &dst);

    float trackRatio = (float)(scene->trackTime / track->duration);
    trackRatio = Float_clamp(trackRatio, 0.0f, 1.0f);
    dst.x += 2; dst.y += 2;
    dst.w -= 4; dst.h -= 4;
    dst.w = (int)(trackRatio * dst.w);

    color = assets->colors.white;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &dst);

    //* DEBUG
    // Gizmos du canvas en jaune
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &(g_levelRects.points));
    SDL_RenderDrawRect(renderer, &(g_levelRects.uiRect));
    SDL_RenderDrawRect(renderer, &(g_levelRects.progressBar));
    //*/
}

void LevelCanvas_update(LevelCanvas *self)
{
    Track *track = LevelScene_getTrack(self->scene);
    LevelScore score = LevelScene_getScore(self->scene);
    char buffer[128] = { 0 };
    
    // Met à jour l'affichage du nombre de points du joueur
    sprintf(buffer, "%d", (int)score.points);
    Text_setString(self->textPoints, buffer);
}
