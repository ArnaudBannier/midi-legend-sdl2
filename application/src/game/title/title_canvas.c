/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/title/title_canvas.h"
#include "game/title/title_scene.h"
#include "utils/math.h"

TitleCanvas *TitleCanvas_create(TitleScene *scene)
{
    TitleCanvas *self = (TitleCanvas *)calloc(1, sizeof(TitleCanvas));
    AssertNew(self);

    AssetManager *assets = TitleScene_getAssetManager(scene);
    SDL_Renderer *renderer = TitleScene_getRenderer(scene);

    self->scene = scene;

    self->textSelectMusic = Text_create(renderer, assets->fonts.normal, u8"Musique", assets->colors.blue);
   // self->textMusic = Text_create(renderer, assets->fonts.normal, u8"Nom de la musique", assets->colors.blue);  // TODO : decommenter
    self->textStart = Text_create(renderer, assets->fonts.normal, u8"Commencer", assets->colors.blue);

    return self;
}

void TitleCanvas_destroy(TitleCanvas *self)
{
    if (!self) return;

    //Text_destroy(self->textMusic);  // TODO : decommenter
    Text_destroy(self->textSelectMusic);
    Text_destroy(self->textStart);

    free(self);
}

void TitleCanvas_render(TitleCanvas *self)
{
    TitleScene *scene = self->scene;
    SDL_Renderer *renderer = TitleScene_getRenderer(scene);

    int w, h;
    SDL_Rect dst = { 0 };
    SDL_Texture *texture = NULL;

    // Choix de la musique
    texture = Text_getTexture(self->textSelectMusic);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    dst.x = g_titleRects.textSelectMusic.x;
    dst.y = g_titleRects.textSelectMusic.y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    /*// TODO : decommenter
    texture = Text_getTexture(self->textMusic);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    dst.x = g_titleRects.textMusic.x;
    dst.y = g_titleRects.textMusic.y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    */

    // Commencer
    texture = Text_getTexture(self->textStart);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    dst.x = g_titleRects.textStart.x;
    dst.y = g_titleRects.textStart.y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    //* DEBUG
    // Gizmos du canvas en jaune
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &(g_titleRects.textSelectMusic));
    SDL_RenderDrawRect(renderer, &(g_titleRects.textStart));
    SDL_RenderDrawRect(renderer, &(g_titleRects.textMusic));
    //*/
}

bool TitleCanvas_update(TitleCanvas *self)
{
    TitleScene *scene = self->scene;
    AssetManager *assets = TitleScene_getAssetManager(scene);
    Input *input = TitleScene_getInput(scene);
    LevelConfig *config = TitleScene_getLevelConfig(scene);

    if (input->downPressed || input->upPressed)
    {
        int idx = self->selection;
        idx += (input->downPressed) ? 1 : -1;
        idx = Int_clamp(idx, 0, 1);

        self->selection = idx;
    }

    if (input->leftPressed || input->rightPressed)
    {
        if (self->selection == 0)
        {
            int idx = config->musicID;
            idx += (input->rightPressed) ? 1 : -1;
            idx = (idx + MUSIC_COUNT) % MUSIC_COUNT;
            config->musicID = idx;
        }
    }

    //Text_setString(self->textMusic, g_musics[config->musicID].titleName);   // TODO : decommenter

    Text *leftTexts[] = {
        self->textSelectMusic,
        self->textStart
    };
    for (int i = 0; i < 2; i++)
    {
        SDL_Color colors = (i == self->selection) ?
            assets->colors.green : assets->colors.blue;
        Text_setColor(leftTexts[i], colors);
    }

    return (self->selection == 1 && input->startPressed);
}
