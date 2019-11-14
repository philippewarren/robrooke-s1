#ifndef DEL_COULEUR_H
#define DEL_COULEUR_H

#include <Arduino.h>
#include "capteur_couleur.h"

#define PORT_ROUGE 38
#define PORT_VERT 40
#define PORT_BLEU 42

//Initialise les ports utilisés par les canaux de couleur de la DEL couleurée
void initialiserPortsDELCouleur();

//Allume la DEL couleurée et retourne la couleur
int allumerDELCouleur(int couleur);

//Eteint la DEL couleurée
void eteindreDELCouleur();


#endif