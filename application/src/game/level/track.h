/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"

typedef struct LevelScene LevelScene;

// Duree minimale pour qu'une note soit considérée comme longue
#define MINIMAL_LONG_NOTE 0.3

/// @brief Enumération des deux types d'une note (courte/longue).
typedef enum NoteType
{
    /// @brief Type d'une note courte.
    TYPE_SHORT,

    /// @brief Type d'une note longue.
    TYPE_LONG
} NoteType;

/// @brief Enumération des états possibles d'une note.
typedef enum NoteState
{
    /// @brief Etat d'une note en cours de descente.
    NOTE_ACTIVE,

    /// @brief Etat d'une note jouée et validée.
    NOTE_PLAYED,

    /// @brief Etat d'une note (longue) qui est maintenue.
    NOTE_HELD,

    /// @brief Etat d'une note (longue) qui a été jouée mais pas maintenue jusqu'à sa fin.
    NOTE_RELEASED,

    /// @brief Etat d'une note ratée.
    NOTE_FAILED
} NoteState;

/// @brief Structure représentant une note.
typedef struct Note
{
    /// @brief Type de la note (courte ou longue).
    NoteType type;

    /// @brief Etat de la note (active, jouée, ratée...).
    NoteState state;

    /// @brief Identifiant de la touche/corde sur laquelle la note doit être jouée.
    int keyID;

    /// @brief Valeur/hauteur de la note selon la norme MIDI.
    /// Plus cette valeur est grande, plus la note est aiguë (fréquence élevée).
    int value;

    /// @brief Temps de début de la note.
    float playingTime;

    /// @brief Temps de fin de la note.
    float endingTime;

    /// @brief Durée de la note (= endingTime - playingTime).
    float duration;
} Note;

/// @brief Structure représentant la piste du jeu.
/// Il s'agit de la structure principale du jeu.
typedef struct Track
{
    /// @brief La scène du niveau.
    LevelScene *scene;

    /// @brief Nombre de notes de la piste.
    int noteCount;

    /// @brief Tableau des notes de la piste.
    Note *notes;

    /// @brief Nombre de touches/cordes pour le joueur.
    int keyCount;

    /// @brief Temps visible par le joueur.
    /// Correspond au temps qu'une note met pour parcourir entièrement la zone visible.
    float visibleTime;

    /// @brief Temps passé visible par le joueur.
    /// Correspond au temps qu'une note met pour parcourir la zone entre
    /// la ligne de validation du joueur et le bas de la piste.
    float pastTime;

    /// @brief Durée de la musique.
    /// Correspond au temps de fin de la dernière note
    /// (+ 1s pour prendre en compte la réverbération).
    float duration;

    /// @brief Indice de la première note visible dans le tableaux des notes.
    int firstIdx;

    /// @brief Indice de la dernière note visible dans le tableau des notes.
    int lastIdx;
} Track;

/// @brief Crée la piste du niveau.
/// @param scene la scène.
/// @param filename le chemin du fichier contenant la partition.
/// @return La piste créée.
Track *Track_create(LevelScene *scene, char *filename);

/// @brief Détruit la piste du niveau.
/// @param self la piste.
void Track_destroy(Track *self);

/// @brief Supprime les accords (plusieurs notes jouées en même temps).
/// Cela permet de simplifier le placement des notes et le gameplay.
/// @param self la piste.
void Track_clearChords(Track *self);

/// @brief Algorithme de placement des notes sur les touches/cordes pour le joueur.
/// Se base sur les valeurs (ou hauteurs) réelles des notes pour donner un gameplay cohérent.
/// @param self la piste.
/// @param keyCount le nombre de touches/cordes pour le joueur.
void Track_placeNotes(Track *self, int keyCount);

/// @brief Met à jour la piste.
/// Cette méthode analyse les actions du joueur ainsi que l'état de piste
/// pour déterminer les notes validées ou ratées.
/// Elle met également à jour le score du joueur.
/// @param self la piste.
void Track_update(Track *self);

/// @brief Dessine la piste dans le moteur de rendu.
/// @param self la piste.
void Track_render(Track *self);
