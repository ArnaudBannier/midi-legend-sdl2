/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "common.h"
#include "game/asset_manager.h"
#include "game/title/title_scene.h"
#include "game/level/level_scene.h"
#include "utils/math.h"

Timer *g_time = NULL;
TitleRects g_titleRects = { 0 };
LevelRects g_levelRects = { 0 };
MusicSpec g_musics[MUSIC_COUNT] = { 0 };

void Game_initRectangles()
{
    int textHeight = 15; // TODO : Adapter la hauteur de texte
    int y;

    //--------------------------------------------------------------------------
    // Menu principal

    int xMid = LOGICAL_WIDTH / 2;
    
    y = 2 * LOGICAL_HEIGHT / 3;

    //SDL_Rect_set(&(g_titleRects.textSelectMusic), xMid - 400, y, 400, textHeight);   // TODO : decommenter/modifier
    //SDL_Rect_set(&(g_titleRects.textMusic), xMid, y, 400, textHeight);  // TODO : decommenter/modifier

    y += textHeight + 30;
    //SDL_Rect_set(&(g_titleRects.textStart), xMid - 400, y, 400, textHeight);  // TODO : decommenter/modifier

    //--------------------------------------------------------------------------
    // Niveau

    int trackWidth = 600;     // TODO : modifier;
    int trackHeight = 250;    // TODO : modifier;
    int xTrack = 30;

    //SDL_Rect_set(&(g_levelRects.logo), xTrack, 0, trackWidth, 211);  // TODO : decommenter/modifier
    //SDL_Rect_set(&(g_levelRects.trackFill), xTrack, 211, trackWidth, trackHeight);  // TODO : decommenter/modifier
    //SDL_Rect_set(&(g_levelRects.trackMask), xTrack, 211, trackWidth, 100);  // TODO : decommenter/modifier

    int barH = 13;
    int uiWidth = 300;
    int xUI = LOGICAL_WIDTH - uiWidth - 30;

    y = 0;
    //SDL_Rect_set(&(g_levelRects.uiRect), xUI, y, uiWidth, 300);  // TODO : decommenter/modifier

    y += 20;
    //SDL_Rect_set(&(g_levelRects.points), xUI, y, uiWidth, textHeight);  // TODO : decommenter/modifier

    y += textHeight + 30;
    //SDL_Rect_set(&(g_levelRects.progressBar), xUI, y, uiWidth, barH);  // TODO : decommenter/modifier
}

void Game_init(int sdlFlags, int imgFlags)
{
    // Initialise la SDL2
    if (SDL_Init(sdlFlags) < 0)
    {
        printf("ERROR - SDL_Init %s\n", SDL_GetError());
        assert(false);
        abort();
    }

    // Initialise la SDL2 image
    if (IMG_Init(imgFlags) != imgFlags)
    {
        printf("ERROR - IMG_Init %s\n", IMG_GetError());
        assert(false);
        abort();
    }

    // Initialise la SDL2 TTF
    if (TTF_Init() == -1)
    {
        printf("ERROR - TTF_Init %s\n", TTF_GetError());
        assert(false);
        abort();
    }

    // Initialise la SDL2 Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        printf("ERROR - Mix_OpenAudio %s\n", Mix_GetError());
        assert(false);
        abort();
    }
    Mix_AllocateChannels(8);

    // Initialise les rectangles fixes du jeu utilisés pour le rendu
    Game_initRectangles();

    int musicID = 0;
    g_musics[musicID].textPath = ASSET_PATH "musics/island_village.txt";
    g_musics[musicID].musicPath = ASSET_PATH "musics/island_village.mp3";
    g_musics[musicID].titleName = "< Island Village >";
    g_musics[musicID].fullName = "Island Village";
    g_musics[musicID].composer = "Heatley Bros - Heatley Bros V";

    musicID++;
    g_musics[musicID].textPath = ASSET_PATH "musics/new_challenger.txt";
    g_musics[musicID].musicPath = ASSET_PATH "musics/new_challenger.mp3";
    g_musics[musicID].titleName = "< New Challenger >";
    g_musics[musicID].fullName = "New Challenger";
    g_musics[musicID].composer = "Heatley Bros - Heatley Bros V";

    musicID++;
    g_musics[musicID].textPath = ASSET_PATH "musics/fight_or_flight.txt";
    g_musics[musicID].musicPath = ASSET_PATH "musics/fight_or_flight.mp3";
    g_musics[musicID].titleName = "< Fight Or Flight >";
    g_musics[musicID].fullName = "Fight Or Flight";
    g_musics[musicID].composer = "Heatley Bros - Heatley Bros VI";

    // Crée le temps global du jeu
    g_time = Timer_create();
    AssertNew(g_time);
}

void Game_quit()
{
    Timer_destroy(g_time);
    g_time = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
