#ifndef SUIVEUR_LIGNE_H
#define SUIVEUR_LIGNE_H

#include <Arduino.h>
#include <LibRobus.h>
#include "mouvement.h"

#define CAPTEUR_GAUCHE 5
#define CAPTEUR_DROIT 2

extern volatile int bouton;

//ne peu pas être utilisé en me temps que IR1,IR2,IR3,J20,J21,J22

//constante proportionnelle à la différence de réflectivité des deux surfaces
// 1000 = sol blanc et ligne noir
const short CONTRASTE = 1000;

extern const int pin;

//fait une lecture du suiveur de ligne et place le résultat dans output
void lireSuiveurLigne(int output [8]);

//modifie la vitesse des moteur pour permettre au robot de suivre une ligne une vitesse inférieur à 0.5 est recommendée
void suivreLigne(float vitesse);


//affiche une ligne
void afficherLigne(int ligne[8]);

//trouve une ligne, la suis et arrête à la fin en étant bloquant
void traquerLigneBloque(float vitesse);

//transforme un tableau contenant les valeurs d'un suiveur de ligne en 0 et en 1
void estLigneHuit(int lectures[8]);

bool lignePerpendiculaire();




#endif