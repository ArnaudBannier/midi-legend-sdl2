/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/input.h"
#include "common.h"

void InputConfig_init(InputConfig *config, bool pianoMode)
{
    assert(config);

    config->pianoMode = pianoMode;

    if (pianoMode)
    {
        config->keyCodes[0] = SDL_SCANCODE_Q;
        config->keyCodes[1] = SDL_SCANCODE_W;
        config->keyCodes[2] = SDL_SCANCODE_E;
        config->keyCodes[3] = SDL_SCANCODE_R;
        config->keyCodes[4] = SDL_SCANCODE_SPACE;
    }
    else
    {
        config->keyCodes[0] = SDL_SCANCODE_F1;
        config->keyCodes[1] = SDL_SCANCODE_F2;
        config->keyCodes[2] = SDL_SCANCODE_F3;
        config->keyCodes[3] = SDL_SCANCODE_F4;
        config->keyCodes[4] = SDL_SCANCODE_F5;
    }
    config->strumCode = SDL_SCANCODE_RETURN;
}

Input *Input_create(bool pianoMode)
{
    Input *self = (Input *)calloc(1, sizeof(Input));
    AssertNew(self);

    InputConfig_init(&(self->config), pianoMode);

    return self;
}

void Input_destroy(Input *self)
{
    if (!self) return;
    free(self);
}

void Input_update(Input *self)
{
    bool strumPressed = false;

    self->quitPressed = false;
    self->startPressed = false;
    self->menuPressed = false;

    self->upPressed = false;
    self->downPressed = false;
    self->leftPressed = false;
    self->rightPressed = false;

    for (int i = 0; i < MAX_KEY_COUNT; i++)
    {
        self->keyHit[i] = false;
    }

    SDL_Event evt;
    SDL_Scancode code;
    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            self->quitPressed = true;
            break;

        case SDL_KEYDOWN:
            if (evt.key.repeat)
                break;

            code = evt.key.keysym.scancode;
            switch (code)
            {
            case SDL_SCANCODE_ESCAPE:
                self->quitPressed = true;
                break;

            case SDL_SCANCODE_RIGHT:
                // Deplacement à droite
                self->rightPressed = true;
                break;

            case SDL_SCANCODE_LEFT:
                // Deplacement à gauche
                self->leftPressed = true;
                break;

            case SDL_SCANCODE_UP:
                // Deplacement en haut
                self->upPressed = true;
                break;

            case SDL_SCANCODE_DOWN:
                // Deplacement en bas
                self->downPressed = true;
                break;

            case SDL_SCANCODE_RETURN:
                self->startPressed = true;
                break;

            case SDL_SCANCODE_DELETE:
            case SDL_SCANCODE_BACKSPACE:
                self->menuPressed = true;
                break;

            default:
                break;
            }

            if (self->config.pianoMode)
            {
                for (int i = 0; i < MAX_KEY_COUNT; i++)
                {
                    if (code == self->config.keyCodes[i])
                    {
                        self->keyDown[i] = true;
                        self->keyHit[i] = true;
                    }
                }
            }
            else
            {
                for (int i = 0; i < MAX_KEY_COUNT; i++)
                {
                    if (code == self->config.keyCodes[i])
                    {
                        self->keyDown[i] = true;
                    }
                }
                if (code == self->config.strumCode)
                {
                    strumPressed = true;
                }
            }
            break;

        case SDL_KEYUP:
            code = evt.key.keysym.scancode;
            for (int i = 0; i < MAX_KEY_COUNT; i++)
            {
                if (code == self->config.keyCodes[i])
                {
                    self->keyDown[i] = false;
                }
            }
            break;
        }
    }

    if (strumPressed)
    {
        for (int i = 0; i < MAX_KEY_COUNT; i++)
        {
            self->keyHit[i] = self->keyDown[i];
        }
    }
}
