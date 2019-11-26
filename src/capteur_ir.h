#ifndef CAPTEUR_IR_H
#define CAPTEUR_IR_H

#include <LibRobus.h>
#include "conversions.h"

#define INTERNE 0
#define EXTERNE 1

//Légèrement < distance entre les pinces
#define SEUIL_LETTRE_INTERNE 10
//Légèrement < distance entre les postes
#define SEUIL_LETTRE_EXTERNE 20

//Prend un tableau d'int et sa longueur, et classe les membres du tableau en ordre croissant
void classerTableauCroissant(uint16_t tableau[], const int NB_ELEMENTS);

//Prend un tableau d'int et sa longueur (impaire), et renvoie la mediane parmi ses membres
uint16_t calculerMediane(uint16_t tableau[], const int NB_ELEMENTS);

//Utilisée pour lire directement une valeur entre 0 et 1023 du capteur IR (index entre 0 et 3), en prenant amplitude*2-1 mesures
uint16_t lireValeurIR(uint8_t capteur, uint8_t amplitude = 5);

//Retourne vrai si une lettre est dans la pince
bool estLettrePince();

//Retourne vrai si une lettre est dans le bac suivant
bool estLettreSuivant();

void debugCapteurIR(uint8_t capteur);

void debugEstLettre();


#endif