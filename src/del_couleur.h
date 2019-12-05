#ifndef DEL_COULEUR_H
#define DEL_COULEUR_H

#include <Arduino.h>
#include "capteur_couleur.h"

#define PORT_ROUGE 38
#define PORT_VERT 40
#define PORT_BLEU 42
#define PORT_JAUNE 44

//Allume la DEL de couleur correspondante et retourne la couleur, une autre valeur éteint les 4 DEL
int allumerDELCouleur(int couleur);

//Eteint les DEL de couleur
void eteindreDELCouleur();


#endif