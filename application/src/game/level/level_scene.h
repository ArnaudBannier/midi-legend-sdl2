/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "common.h"

#include "game/asset_manager.h"
#include "game/level/level_canvas.h"
#include "game/input.h"
#include "game/level/track.h"

/// @brief Structure représentant les élements servant au score du joueur.
/// Peut également contenir le nombre de combo, la valeur du multiplicateur, la précision...
typedef struct LevelScore
{
    /// @brief Nombre de points du joueur.
    float points;
} LevelScore;

/// @brief Structure représentant la scène principale du jeu (niveau).
typedef struct LevelScene
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la scène (textures, fontes, couleurs, son...).
    AssetManager *assets;

    /// @brief Musique du niveau.
    Mix_Chunk *music;

    /// @brief Piste du niveau. Il s'agit de la zone de jeu.
    Track *track;

    /// @brief Temps courant dans la musique.
    /// Sa valeur est négative avant que la musique ne commence.
    double trackTime;

    /// @brief Booléen indiquant si la musique est en train d'être jouée.
    /// Est à false uniquement au début du niveau.
    bool playing;

    /// @brief Entrées utilisateur.
    Input *input;

    /// @brief Canvas. Correspond à l'interface utilisateur (UI).
    LevelCanvas *canvas;

    /// @brief Score du joueur.
    /// Contient les informations essentielles de l'interface utilisateur (UI).
    LevelScore score;
} LevelScene;

/// @brief Crée la scène du niveau.
/// @param renderer le moteur de rendu.
/// @param musicID l'identifiant de la musique.
/// @param keyCount le nombre de touches.
/// @param pianoMode booléen indiquant si le jeu est en mode piano (ou guitare).
/// @return La scène créée.
LevelScene *LevelScene_create(
    SDL_Renderer *renderer, int musicID,
    int keyCount, bool pianoMode);

/// @brief Détruit la scène du niveau.
/// @param self la scène.
void LevelScene_destroy(LevelScene *self);

/// @brief Initialise la scène du niveau.
/// @param self la scène.
void LevelScene_start(LevelScene *self);

/// @brief Met à jour la scène.
/// Cette fonction est appelée à chaque tour de la boucle de rendu.
/// @param self la scène.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool LevelScene_update(LevelScene *self);

/// @brief Dessine la scène dans le moteur de rendu.
/// @param self la scène.
void LevelScene_render(LevelScene *self);

/// @brief Renvoie le moteur de rendu de la scène.
/// @param self la scène.
/// @return Le moteur de rendu de la scène.
INLINE SDL_Renderer *LevelScene_getRenderer(LevelScene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la scène.
/// @param self la scène.
/// @return Les assets de la scène.
INLINE AssetManager *LevelScene_getAssetManager(LevelScene *self)
{
    return self->assets;
}

/// @brief Renvoie les entrées utilisateur de la scène.
/// @param self la scène.
/// @return Les entrées utilisateur de la scène.
INLINE Input *LevelScene_getInput(LevelScene *self)
{
    return self->input;
}

/// @brief Renvoie la piste (structure principale du jeu) de la scène.
/// @param self la scène.
/// @return La piste de la scène.
INLINE Track *LevelScene_getTrack(LevelScene *self)
{
    return self->track;
}

/// @brief Renvoie la structure contenant toutes les informations sur le score du joueur.
/// @param self la scène.
/// @return Le score du joueur.
INLINE LevelScore LevelScene_getScore(LevelScene *self)
{
    return self->score;
}

/// @brief Définit le score du joueur.
/// @param self la scène.
/// @param score le nouveau score du joueur.
INLINE void LevelScene_setScore(LevelScene *self, LevelScore score)
{
    self->score = score;
}
