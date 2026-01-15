/*
    Copyright (c) Arnaud BANNIER and Nicolas BODIN.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "game/level/track.h"
#include "game/level/level_scene.h"
#include "utils/math.h"

/// @brief Indique si une note a déjà parcouru la zone de la piste visible
/// par le joueur.
/// @param self la note.
/// @param track la piste.
/// @return true si la note est passée,
/// false si elle est actuellement visble ou si elle sera visible.
bool Note_isPast(Note *self, Track *track)
{
    float trackTime = (float)(track->scene->trackTime);
    return (self->endingTime < trackTime - track->pastTime);
}

/// @brief Indique si une note n'est pas entre apparue dans la zone
/// de la piste visible par le joueur.
/// @param self la note.
/// @param track la piste.
/// @return true si la note n'est pas encore apparue,
/// false si elle est actuellement visble ou si elle l'a déjà été.
bool Note_isFutur(Note *self, Track *track)
{
    float trackTime = (float)(track->scene->trackTime);
    float futurTime = track->visibleTime - track->pastTime;
    return (self->playingTime > trackTime + futurTime);
}

/// @brief Met à jour les indices de la première note et de la dernière note
/// qui sont visibles par joueur dans la piste.
/// @param self la piste.
void Track_updateVisibleRange(Track *self)
{
    int noteCount = self->noteCount;
    for (int i = self->firstIdx; i < noteCount; i++)
    {
        Note *note = self->notes + i;

        if (Note_isPast(note, self))
        {
            self->firstIdx++;
            continue;
        }

        if (Note_isFutur(note, self))
        {
            self->lastIdx = i;
            break;
        }
    }
}

Track *Track_create(LevelScene *scene, char *filename)
{
    FILE *file = fopen(filename, "r");
    AssertNew(file);

    Track *self = (Track *)calloc(1, sizeof(Track));
    AssertNew(self);

    int scanCount = 0;
    int noteCount = 0;
    float duration = 0.0f;
    float timeShift = 0.0f;

    scanCount = fscanf(file, "%d", &noteCount);
    assert(scanCount == 1);

    scanCount = fscanf(file, "%f", &timeShift);
    assert(scanCount == 1);

    scanCount = fscanf(file, "%f", &duration);
    assert(scanCount == 1);

    self->scene = scene;
    self->keyCount = 1;
    self->noteCount = noteCount;
    self->duration = duration;

    self->notes = (Note *)calloc(noteCount, sizeof(Note));
    AssertNew(self->notes);

    self->visibleTime = 2.0f;
    self->pastTime = 0.15f * self->visibleTime;

    for (int i = 0; i < noteCount; i++)
    {
        Note *note = self->notes + i;

        scanCount = fscanf(file, "%d", &(note->value));
        assert(scanCount == 1);

        scanCount = fscanf(file, "%f", &(note->playingTime));
        assert(scanCount == 1);

        scanCount = fscanf(file, "%f", &(note->duration));
        assert(scanCount == 1);

        note->playingTime += timeShift;
        note->endingTime = note->playingTime + note->duration;

        if (note->duration >= MINIMAL_LONG_NOTE)
        {
            note->type = TYPE_LONG;
        }
        else
        {
            note->type = TYPE_SHORT;
        }
    }

    fclose(file);

    return self;
}

void Track_destroy(Track *self)
{
    if (!self) return;

    free(self->notes);
    free(self);
}

void Track_clearChords(Track *self)
{
    assert(self && self->notes);

    Note *notes = self->notes;
    int noteCount = self->noteCount;

    int noteIdx = 1;
    for (int i = 1; i < noteCount; i++)
    {
        if (notes[i].playingTime - notes[i - 1].playingTime >= 0.05)
        {
            notes[noteIdx++] = notes[i];
        }
    }
    self->noteCount = noteIdx;
}

void Track_placeNotes(Track *self, int keyCount)
{
    assert(self && self->notes);

    self->keyCount = keyCount;

    Note *notes = self->notes;
    int noteCount = self->noteCount;

    // TODO : Ameliorer le placement des notes   
    for (int i = 0; i < noteCount; i++)
    {
        notes[i].keyID = rand() % keyCount;
    }
    
}

void Track_update(Track *self)
{
    LevelScene *scene = self->scene;
    Input *input = LevelScene_getInput(scene);
    LevelScore score = LevelScene_getScore(scene);
    float trackTime = (float)scene->trackTime;

    // Met à jour les indices des notes visibles par le joueur
    // Cela évite de parcourir toutes les notes de la musique
    // à chaque frame (optimisation).
    Track_updateVisibleRange(self);

    // Modifie l'état des notes visibles par le joueur
    for (int i = self->firstIdx; i <= self->lastIdx; i++)
    {
        Note *note = self->notes + i;
        int keyID = note->keyID;

        if (note->state == NOTE_ACTIVE)
        {
            // La note est active, elle est donc en cours de descente
            // et n'a pas encore été traitée par le joueur
            
            if (fabsf(note->playingTime - trackTime) < 0.5f && input->keyHit[keyID])  // TODO : adapter le timer
            {
                // L'écart entre le temps courant de la musique et le début
                // de la note est inférieur à 0.5s
                // et le joueur vient d'appuyer sur la bonne touche

                score.points++;
                note->state = NOTE_PLAYED;
            }
            else if (note->playingTime + 0.2f < trackTime)
            {
                // La note devait être jouée il y a plus de 0.2s

                note->state = NOTE_FAILED;
            }
        }
    }

    // Met à jour le score du joueur
    //LevelScene_setScore(scene, score);  // TODO : decommenter
}

/// @brief Calcule la position relative d'une note dans la zone visible par le joueur.
/// Elle vaut 0.0f pour une note future (en haut) qui vient d'être visible par le joueur.
/// Elle vaut 1.0f pour une note passée (en bas) qui vient de ne plus être visible par le joueur.
/// @param self la piste.
/// @param note la note.
/// @return La position relative de la note dans la zone visible par le joueur.
float Track_getNoteRelativePosition(Track *self, Note *note)
{
    float trackTime = (float)self->scene->trackTime;
    float relativeNotePos = 1.0f - (note->playingTime - trackTime + self->pastTime) / self->visibleTime;
    return Float_clamp(relativeNotePos, -0.05f, 1.05f);
}

void Track_render(Track *self)
{
    LevelScene *scene = self->scene;
    AssetManager *assets = LevelScene_getAssetManager(scene);
    Input *input = LevelScene_getInput(scene);
    SDL_Renderer *renderer = LevelScene_getRenderer(scene);

    // Dessine le fond de la piste
    SDL_Rect trackRect = g_levelRects.trackFill;
    //SDL_RenderCopy(renderer, assets->textures.trackFill, NULL, &trackRect); // TODO : decommenter

    // Boucle de rendu des notes
    for (int i = self->firstIdx; i <= self->lastIdx; i++)
    {
        Note *note = &(self->notes[i]);

        // Si la note est jouée, on ne la dessine pas
        if (note->state == NOTE_PLAYED) continue;

        // On récupère la texture du la note
        SDL_Texture *texture = assets->textures.note;

        // On modifie son opacité en fonction de l'état de la note
        // 0 = complètement transparent, 255 = complètement opaque
        Uint8 alpha = (note->state == NOTE_FAILED) ? 100 : 255;
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, alpha);

        // On calcule la position relative de la note dans la piste.
        float noteRelPos = Track_getNoteRelativePosition(self, note);

        // On définit la position et les dimensions de la note
        SDL_Rect dst = { 0 };
        dst.w = 37;
        dst.h = 25;
        dst.x = trackRect.x + note->keyID * 50;
        dst.y = (int)(trackRect.y + noteRelPos * trackRect.h);
        dst.y -= dst.h;

        // On dessine la note
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }

    // Calcule la position relative de la ligne de validation du joueur
    // dans la piste.
    float validationRelPos = 1.0f - self->pastTime / self->visibleTime;

    // Boucle de rendu des touches du joueur
    for (int i = 0; i < self->keyCount; i++)
    {
        SDL_Rect dst = { 0 };
        dst.w = 37;
        dst.h = 25;
        dst.x = trackRect.x + i * 50;
        dst.y = (int)(trackRect.y + validationRelPos * trackRect.h);
        dst.y -= dst.h;

        SDL_Texture *texture = input->keyDown[i] ? assets->textures.keyDown : assets->textures.keyUp;
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }

    // On dessine le masque en dernier (pour qu'il soit au dessus des notes)
    SDL_RenderCopy(renderer, assets->textures.trackMask, NULL, &(g_levelRects.trackMask));


    //* DEBUG
    // Gizmos de la piste en magenta
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &(g_levelRects.trackMask));
    SDL_RenderDrawRect(renderer, &(g_levelRects.trackFill));
    //*/
}
