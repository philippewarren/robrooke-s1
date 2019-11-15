#ifndef CAPTEUR_IR_H
#define CAPTEUR_IR_H

#include <LibRobus.h>
#include "operations_generales.h"
#include "conversions.h"

#define INTERNE 0
#define EXTERNE 1

//Légèrement < distance entre les pinces
#define SEUIL_LETTRE_INTERNE 10
//Légèrement < distance entre les postes
#define SEUIL_LETTRE_EXTERNE 20

//Utilisée pour lire une valeur de distance en cm du capteur IR (index entre 0 et 3), en prenant amplitude*2-1 mesures
float lireDistanceIR(uint8_t capteur, uint8_t amplitude = 3);

//Retourne vrai si le capteur détecte une lettre
bool estLettre(uint8_t capteur);

//Retourne vrai si une lettre est dans la pince
bool estLettrePince();

//Retourne vrai si une lettre est dans le bac suivant
bool estLettreSuivant();


#endif