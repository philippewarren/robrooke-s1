#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <LibRobus.h>
#include "conversions.h"

//Reset les deux encodeurs
void resetDeuxEncodeurs();

//NE JAMAIS UTILISER
//bool estChangeDeDirection(uint8_t moteur, float nouvelleVitesse);

//Change la vitesse d'un moteur, en ajoutant un cours délais si la direction change
void changerVitesseMoteur(uint8_t moteur, float nouvelleVitesse);

//Change la vitesse des deux moteurs, en ajoutant un cours délais si la direction change.
//Si un seul argument est passé, les deux moteurs sont mis à la même vitesse.
void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD = 200.0);

//Met la vitesse des deux moteurs à 0
void arreterDeuxMoteurs();

//PID retourne différence droite-gauche
float partielIntegralDerive(float multiRoueDroite = 1,bool reset = 0);
//mouvement non bloquant
bool avancerDroit(float vitesse, float distance);











#endif