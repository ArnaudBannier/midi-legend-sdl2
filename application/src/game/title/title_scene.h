/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "common.h"

#include "game/asset_manager.h"
#include "game/title/title_canvas.h"
#include "game/input.h"
#include "game/level/track.h"

/// @brief Structure représentant les paramètres du niveau sélectionné dans le menu principal.
typedef struct LevelConfig
{
    /// @brief Identifiant de la musique.
    int musicID;

    /// @brief Nombre de touches/cordes du niveau (typiquement 3 à 5).
    int keyCount;

    /// @brief Booléen indiquant si le niveau est joué en mode piano (true) ou guitare (false).
    bool piano;
} LevelConfig;

/// @brief Structure représentant la scène principale du jeu (niveau).
typedef struct TitleScene
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la scène (textures, fontes, couleurs, son...).
    AssetManager *assets;

    /// @brief Entrées utilisateur.
    Input *input;

    /// @brief Canvas. Correspond à l'interface utilisateur (UI).
    TitleCanvas *canvas;

    /// @brief Paramètres du niveau sélectionné
    /// (choix de la musique, du mode de jeu, du nombre de touches).
    LevelConfig config;

} TitleScene;

/// @brief Crée la scène principale du jeu.
/// @param renderer moteur de rendu.
/// @return La scène créée.
TitleScene *TitleScene_create(SDL_Renderer *renderer);

/// @brief Détruit la scène principale.
/// @param self la scène.
void TitleScene_destroy(TitleScene *self);

/// @brief Met à jour la scène.
/// Cette fonction est appelée à chaque tour de la boucle de rendu.
/// @param self la scène.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool TitleScene_update(TitleScene *self);

/// @brief Dessine la scène dans le moteur de rendu.
/// @param self la scène.
void TitleScene_render(TitleScene *self);

/// @brief Renvoie le moteur de rendu de la scène.
/// @param self la scène.
/// @return Le moteur de rendu de la scène.
INLINE SDL_Renderer *TitleScene_getRenderer(TitleScene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la scène.
/// @param self la scène.
/// @return Les assets de la scène.
INLINE AssetManager *TitleScene_getAssetManager(TitleScene *self)
{
    return self->assets;
}

/// @brief Renvoie les entrées utilisateur de la scène.
/// @param self la scène.
/// @return Les entrées utilisateur de la scène.
INLINE Input *TitleScene_getInput(TitleScene *self)
{
    return self->input;
}

/// @brief Renvoie les paramètres du niveau sélectionné par le menu principal.
/// @param self la scène.
/// @return Les paramètres du niveau sélectionné.
INLINE LevelConfig *TitleScene_getLevelConfig(TitleScene *self)
{
    return &(self->config);
}
