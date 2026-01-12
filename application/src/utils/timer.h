/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"

/// @brief Structure représentant un chronomètre.
typedef struct Timer
{
    /// @brief Temps de départ.
    float m_startTime;

    /// @brief Temps du dernier appel à Timer_update().
    float m_currentTime;

    /// @brief Temps de l'avant dernier appel à Timer_update().
    float m_previousTime;

    /// @brief Ecart entre les deux derniers appels à Timer_update().
    /// Ce membre est affecté par le facteur d'échelle.
    float m_delta;

    /// @brief Ecart entre les deux derniers appels à Timer_update().
    /// Ce membre n'est pas affecté par le facteur d'échelle.
    float m_unscaledDelta;

    /// @brief Facteur d'échelle appliqué au temps.
    float m_scale;

    /// @brief Ecart entre le lancement du timer Timer_start()
    /// et le dernier appel à Timer_update().
    /// Ce membre est affecté par le facteur d'échelle.
    float m_elapsed;

    /// @brief Ecart entre le lancement du timer Timer_start()
    /// et le dernier appel à Timer_update().
    /// Ce membre n'est pas affecté par le facteur d'échelle.
    float m_unscaledElapsed;
} Timer;

/// @brief Crée un nouveau timer.
/// @return Le timer créé.
Timer* Timer_create();

/// @brief Détruit un timer préalablement alloué avec Timer_create().
/// @param self le timer à détruire.
void Timer_destroy(Timer* self);

/// @brief Lance le timer.
/// @param self le timer.
void Timer_start(Timer* self);

/// @brief Met à jour le timer en fonction du temps actuel.
/// Cette fonction est typiquement appelée à chaque tour de la boucle de rendu.
/// @param self le timer.
void Timer_update(Timer* self);

/// @brief Définit le facteur d'échelle de temps appliquée à un timer.
/// Si l'échelle vaut 0.5f, le temps s'écoule deux fois moins rapidement.
/// @param self le timer.
/// @param scale le facteur d'échelle.
INLINE void Timer_setTimeScale(Timer *self, float scale)
{
    assert(self && scale >= 0.0f);
    self->m_scale = scale;
}

/// @brief Renvoie le facteur d'échelle de temps d'un timer.
/// @param self le timer.
/// @return Le facteur d'échelle de temps d'un timer.
INLINE float Timer_getTimeScale(Timer *self)
{
    assert(self);
    return self->m_scale;
}

/// @brief Renvoie l'écart de temps (en secondes) entre les deux derniers
/// appels à la fonction Timer_update().
/// @param self le timer.
/// @return L'écart de temps entre les deux dernières mises à jour.
INLINE float Timer_getDelta(Timer *self)
{
    assert(self);
    return self->m_delta;
}

/// @brief Renvoie l'écart de temps (en secondes) entre les deux derniers
/// appels à la fonction Timer_Update().
/// Cette méthode ne tient pas compte de l'échelle de temps du timer.
/// @param self le timer.
/// @return L'écart de temps entre les deux dernières mises à jour
/// (sans échelle de temps).
INLINE float Timer_getUnscaledDelta(Timer *self)
{
    assert(self);
    return self->m_unscaledDelta;
}

/// @brief Renvoie l'écart de temps (en secondes) entre le lancement du timer
/// avec Timer_start() et le dernier appel à Timer_update().
/// @param self le timer.
/// @return Le nombre de secondes écoulées depuis le lancement du timer et la dernière mise à jour.
INLINE float Timer_getElapsed(Timer *self)
{
    assert(self);
    return self->m_elapsed;
}

/// @brief Renvoie l'écart de temps (en secondes) entre le lancement du timer
/// avec Timer_Start() et le dernier appel à Timer_Update().
/// Cette méthode en tient pas compte de l'échelle de temps du timer.
/// @param self le timer.
/// @return Le nombre de secondes écoulées depuis le lancement du timer et la
/// dernière mise à jour  (sans échelle de temps).
INLINE float Timer_getUnscaledElapsed(Timer *self)
{
    assert(self);
    return self->m_unscaledElapsed;
}
