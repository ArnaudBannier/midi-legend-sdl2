/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "utils/text.h"

typedef struct TitleScene TitleScene;

/// @brief Structure représentant le canvas du menu principal.
/// Correspond à l'interface utilisateur (UI).
typedef struct TitleCanvas
{
    /// @brief La scène du menu principal.
    TitleScene *scene;

    /// @brief Le texte indiquant de sélectionner la musique du niveau.
    Text *textSelectMusic;

    /// @brief Le texte affichant le nom de la musique sélectionnée.
    //Text *textMusic;  // TODO : decommenter

    /// @brief Le texte de début du niveau.
    Text *textStart;

    /// @brief Indice du paramètre sélectionné dans le menu.
    int selection;
} TitleCanvas;

/// @brief Crée le canvas du menu principal.
/// @param scene la scène.
/// @return Le canvas créé.
TitleCanvas *TitleCanvas_create(TitleScene *scene);

/// @brief Détruit le canvas du menu principal.
/// @param self le canvas.
void TitleCanvas_destroy(TitleCanvas *self);

/// @brief Met à jour le canvas du menu principal.
/// @param self le canvas.
bool TitleCanvas_update(TitleCanvas *self);

/// @brief Dessine le canvas du menu principal dans le moteur de rendu.
/// @param self le canvas.
void TitleCanvas_render(TitleCanvas *self);
