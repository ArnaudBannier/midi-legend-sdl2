/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "settings.h"
#include "common.h"
#include "utils/timer.h"
#include "game/level/level_scene.h"
#include "game/title/title_scene.h"

int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------
    // Initialisation

    // Initialise la SDL
    Game_init(SDL_INIT_VIDEO, IMG_INIT_PNG);

    // Crée la fenêtre
    int sdlFlags = 0;
#ifdef FULLSCREEN
    sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif
    SDL_Window *window = SDL_CreateWindow(
        u8"MidiLegend", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, sdlFlags
    );

    if (!window)
    {
        printf("ERROR - Create window %s\n", SDL_GetError());
        assert(false); abort();
    }

    // Crée le moteur de rendu
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (!renderer)
    {
        printf("ERROR - Create renderer %s\n", SDL_GetError());
        assert(false); abort();
    }

    //--------------------------------------------------------------------------
    // Boucle de jeu

    TitleScene *titleScene = NULL;
    LevelScene *levelScene = NULL;
    while (true)
    {
        //......................................................................
        // Menu principal

        titleScene = TitleScene_create(renderer);

        // Boucle de rendu du menu principal
        while (true)
        {
            // Met à jour le temps
            Timer_update(g_time);

            // Met à jour la scène
            bool quitLoop = TitleScene_update(titleScene);
            if (quitLoop)
                break;

            // Efface le rendu précédent
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Dessine la scène
            TitleScene_render(titleScene);

            // Affiche le nouveau rendu
            SDL_RenderPresent(renderer);
        }

        if (titleScene->input->quitPressed)
            break;

        LevelConfig config = *TitleScene_getLevelConfig(titleScene);

        // Détruit la scène du menu principal
        TitleScene_destroy(titleScene);
        titleScene = NULL;

        //......................................................................
        // Niveau

        levelScene = LevelScene_create(
            renderer, config.musicID, config.keyCount, config.piano
        );

        // Boucle de rendu du niveau
        LevelScene_start(levelScene);
        while (true)
        {
            // Met à jour le temps
            Timer_update(g_time);

            // Met à jour la scène
            bool quitLoop = LevelScene_update(levelScene);
            if (quitLoop)
                break;

            // Efface le rendu précédent
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Dessine la scène
            LevelScene_render(levelScene);

            // Affiche le nouveau rendu
            SDL_RenderPresent(renderer);
        }

        if (levelScene->input->quitPressed)
            break;

        // Détruit la scène du niveau
        LevelScene_destroy(levelScene);
        levelScene = NULL;
    }


    //--------------------------------------------------------------------------
    // Libération de la mémoire

    TitleScene_destroy(titleScene);
    titleScene = NULL;

    LevelScene_destroy(levelScene);
    levelScene = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    Game_quit();

    return EXIT_SUCCESS;
}
