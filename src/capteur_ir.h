#ifndef CAPTEUR_IR_H
#define CAPTEUR_IR_H

#include <LibRobus.h>
#include "conversions.h"

#define INTERNE 0
#define EXTERNE 1

//Convertit un int entre 0 et 1023 en float entre 0 et 5 par produit croisé
float entreeAnalogiqueEnTension(uint16_t entreeAnalogique);

//Convertit une tension en distance lue au capteur IR
float tensionEnDistance(float tension);

//Prend un tableau d'int et sa longueur, et classe les membres du tableau en ordre croissant
void classerTableauCroissant(uint16_t tableau[], const int NB_ELEMENTS);

//Prend un tableau d'int et sa longueur (impaire), et renvoie la mediane parmi ses membres
uint16_t calculerMediane(uint16_t tableau[], const int NB_ELEMENTS);

//Lit une distance du capteur IR (index entre 0 et 3), en prenant amplitude*2-1 mesures
float lireDistanceIR(uint8_t capteur, uint8_t amplitude = 3);

//Utilisée pour lire directement une valeur entre 0 et 1023 du capteur IR (index entre 0 et 3), en prenant amplitude*2-1 mesures
uint16_t lireValeurIR(uint8_t capteur, uint8_t amplitude = 5);

//Retourne vrai si une lettre est dans la pince
bool estLettrePince();

//Retourne vrai si une lettre est dans le bac suivant
bool estLettreSuivant();

//Affiche la valeur lue et la distance mesurée par le capteur IR spécifié (0 à 3) à intervalle régulier
void debugCapteurIR(uint8_t capteur);

//Affiche 1 ou 0 selon si une lettre est considérée comme présente ou non pour les deux capteurs, à intervalle régulier
void debugEstLettre();

#endif