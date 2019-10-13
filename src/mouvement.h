#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include <LibRobus.h>
#include "conversions.h"

//Reset les deux encodeurs
void resetDeuxEncodeurs();

//Change la vitesse d'un moteur, en ajoutant un cours délais si la direction change
void changerVitesseMoteur(uint8_t, float);

//Change la vitesse des deux moteurs. Si un seul argument est passé, les deux moteurs sont mis à la même vitesse.
void changerVitesseDeuxMoteurs(float, float);

//Met la vitesse des deux moteurs à 0
void arreterDeuxMoteurs();











#endif