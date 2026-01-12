/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "utils/text.h"

typedef struct LevelScene LevelScene;

/// @brief Structure représentant le canvas du niveau.
/// Correspond à l'interface utilisateur (UI).
typedef struct LevelCanvas
{
    /// @brief La scène du niveau.
    LevelScene *scene;

    /// @brief Texte affichant le nombre de points du joueur.
    Text *textPoints;
} LevelCanvas;

/// @brief Crée le canvas du niveau.
/// @param scene la scène.
/// @return Le canvas créé.
LevelCanvas *LevelCanvas_create(LevelScene *scene);

/// @brief Détruit le canvas du niveau.
/// @param self le canvas.
void LevelCanvas_destroy(LevelCanvas *self);

/// @brief Met à jour le canvas du niveau.
/// @param self le canvas.
void LevelCanvas_update(LevelCanvas *self);

/// @brief Dessine le canvas du niveau dans le moteur de rendu.
/// @param self le canvas.
void LevelCanvas_render(LevelCanvas *self);
