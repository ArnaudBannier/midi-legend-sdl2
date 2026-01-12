/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"

/// @brief Structure représentant d'un texte affichable.
typedef struct Text
{
    char *str;
    TTF_Font *fonts;
    SDL_Color color;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
} Text;

/// @brief Crée un texte affichable.
/// @param renderer le moteur de rendu.
/// @param font la fonte utilisée pour rendre le texte.
/// @param str la chaîne associée au texte.
/// @param color la couleur de rendu.
/// @return Le texte affichable créé.
Text *Text_create(SDL_Renderer *renderer, TTF_Font *font, const char *str, SDL_Color color);

/// @brief Détruit un texte affichable.
/// @param self le texte.
void Text_destroy(Text *self);

/// @brief Change le contenu du texte.
/// @param self le texte.
/// @param str la nouvelle chaîne à rendre.
void Text_setString(Text *self, const char *str);

/// @brief Change le couleur de rendu d'un texte affichable.
/// @param self le texte.
/// @param color la couleur.
void Text_setColor(Text *self, SDL_Color color);

/// @brief Renvoie la chaîne associée à un texte affichable.
/// @param self le texte.
/// @return La chaîne (contenu) du texte.
INLINE const char *Text_getString(Text *self)
{
    return (const char*)(self->str);
}

/// @brief Renvoie la texture (rendu) d'un texte affichable.
/// @param self le texte.
/// @return La texture du texte.
INLINE SDL_Texture *Text_getTexture(Text *self)
{
    return self->texture;
}
