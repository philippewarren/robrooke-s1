#ifndef INTERACTIONS_H
#define INTERACTIONS_H
#include "init_robot.h"
#include <LibRobus.h>
#include <Arduino.h>

#define BOUTON_RESTART 4
#define BOUTON_GAUCHE 0
#define BOUTON_AVANT 2
#define BOUTON_ARRIERE 3
#define BOUTON_DROIT 1

//Contient les ports utilisés pour les 4 DEL aux index 1 à 4, et 0 à l'index 0
extern const byte PORT_DEL[];

//Contient les ports utilisés pour les 5 boutons, avec l'index 4 réservé au bouton
//servant à mettre fin aux interrupt, et les index 0 à 3 pour les autres boutons
//suivant la même numérotation que les bumper (BOUTON_GAUCHE=0;
//BOUTON_DROIT=1; BOUTON_AVANT=2; BOUTON_ARRIERE=3; BOUTON_RESTART=4;)
extern const byte PORT_BOUTON[];

//Utilisé pour l'arrêt d'urgence
extern const byte PORT_INTERRUPT;
//Utilisé pour réactiver le robot après un arrêt d'urgence
extern const byte PORT_RESTART;

//Vrai si clique et relache, faux si ce n'est pas le cas
//Arrière: 3
//Avant: 2
//Gauche: 0
//Droite: 1
bool loopEstCliqueEtRelache(uint8_t);

//Allume une DEL, de 1 (défaut) à 3. 0 allume toutes les DEL
void allumerDEL(uint8_t);

//Éteint une DEL, de 1 (défaut) à 3. 0 éteint toutes les DEL
void eteindreDEL(uint8_t);

//Allume, puis éteint une DEL, de 1 (défaut) à 3, après delais (en ms). 0 flashe toutes les DEL
//Reste allumée pendant une seconde par défaut
void flasherDEL(uint8_t, int);

#endif