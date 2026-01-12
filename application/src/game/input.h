/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"

typedef struct InputConfig
{
    /// @brief Booléen indiquant si le jeu est en mode piano (true) ou guitare (false).
    bool pianoMode;

    /// @brief Valeurs des touches de la piste.
    SDL_Scancode keyCodes[MAX_KEY_COUNT];

    /// @brief Valeur de la touche de validation en mode guitare.
    SDL_Scancode strumCode;
} InputConfig;

void InputConfig_init(InputConfig *config, bool pianoMode);

/// @brief Structure représentant le gestionnaire des entrées utilisateur.
typedef struct Input
{
    /// @brief Configuration des touches de jeu.
    InputConfig config;

    /// @brief Booléen indiquant si le bouton "quitter" vient d'être pressé.
    bool quitPressed;

    /// @brief Booléen indiquant si le bouton "commencer"
    /// vient d'être pressé (menu principal).
    bool startPressed;

    /// @brief Booléen indiquant si le bouton "retour au menu"
    /// vient d'être pressé (niveau).
    bool menuPressed;

    /// @brief Tableau de booléens indiquant les touches de la piste
    /// qui viennent d'être pressées (niveau).
    bool keyHit[MAX_KEY_COUNT];

    /// @brief Tableau de booléens indiquant les touches de la piste
    /// qui sont enfoncées (niveau).
    bool keyDown[MAX_KEY_COUNT];

    /// @brief Booléen indiquant si la flèche directionnelle "haut"
    /// vient d'être pressée (menu principal).
    bool upPressed;

    /// @brief Booléen indiquant si la flèche directionnelle "bas"
    /// vient d'être pressée (menu principal).
    bool downPressed;

    /// @brief Booléen indiquant si la flèche directionnelle "gauche"
    /// vient d'être pressée (menu principal).
    bool leftPressed;

    /// @brief Booléen indiquant si la flèche directionnelle "droite"
    /// vient d'être pressée (menu principal).
    bool rightPressed;
} Input;

/// @brief Crée un nouveau gestionnaire des entrées utilisateur.
/// @param pianoMode indique si le jeu est configuré pour un piano ou un guitare.
/// @return Le gestionnaire des entrées utilisateur créé.
Input *Input_create(bool pianoMode);

/// @brief Détruit un gestionnaire des entrées utilisateur.
/// @param self le gestionnaire des entrées utilisateur.
void Input_destroy(Input *self);

/// @brief Met à jour le gestionnaire des entrées utilisateur.
/// Cette fonction effectue la boucle des événement SDL.
/// @param self le gestionnaire des entrées utilisateur.
void Input_update(Input *self);
