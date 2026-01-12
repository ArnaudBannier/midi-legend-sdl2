/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"

/// @brief Structure contenant l'ensemble des assets du jeu.
/// Cela correspond aux ressources utilisées (textures, fontes, couleurs, son...)
typedef struct AssetManager
{
    /// @brief Ensemble des textures du jeu.
    struct Textures
    {
        /// @brief Texture de fond.
        SDL_Texture *background;

        /// @brief Texture du logo du jeu.
        SDL_Texture *logo;

        /// @brief Texture du fond de la piste.
        //SDL_Texture *trackFill;  // TODO : decommenter

        /// @brief Texture du masque utilisé en haut de la piste pour faire
        /// apparaitre les notes en fondu.
        SDL_Texture *trackMask;

        /// @brief Texture d'une note.
        SDL_Texture *note;

        /// @brief Texture d'une touche non enfoncée de la piste.
        SDL_Texture *keyUp;

        /// @brief Texture d'une touche enfoncée de la piste.
        SDL_Texture *keyDown;
    } textures;

    /// @brief Ensemble des fontes de caractères du jeu.
    struct Fonts
    {
        /// @brief Fonte pour un texte de taille intermédiaire.
        TTF_Font *normal;

        /// @brief Fonte pour un texte de grande taille.
        TTF_Font *big;

        /// @brief Fonte pour un texte de petite taille.
        TTF_Font *small;
    } fonts;

    /// @brief Ensemble des couleurs du jeu.
    struct Colors
    {
        /// @brief Couleur représentant du bleu.
        SDL_Color blue;

        /// @brief Couleur représentant du vert.
        SDL_Color green;

        /// @brief Couleur représentant du noir.
        SDL_Color black;

        /// @brief Couleur représentant du blanc.
        SDL_Color white;
    } colors;
} AssetManager;

/// @brief Crée la structure contenant les assets du jeu.
/// @param renderer le moteur de rendu.
/// @return La structure contenant les assets du jeu.
AssetManager *AssetManager_create(SDL_Renderer *renderer);

/// @brief Détruit la structure contenant les assets du jeu.
/// @param self les assets.
void AssetManager_destroy(AssetManager *self);
