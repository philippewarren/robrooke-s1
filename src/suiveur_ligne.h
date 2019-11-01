#ifndef SUIVEUR_LIGNE_H
#define SUIVEUR_LIGNE_H

#include <Arduino.h>
#include <LibRobus.h>
#include "mouvement.h"

//ne peu pas être utilisé en me temps que IR1,IR2,IR3,J20,J21,J22

//constante proportionnelle à la différence de réflectivité des deux surfaces
// 1000 = sol blanc et ligne noir
const short CONTRASTE = 700;

//fait une lecture du suiveur de ligne et place le résultat dans output
void lireSuiveurLigne(int output [8]);
//modifie la vitesse des moteur pour permettre au robot de suivre une ligne une vitesse inférieur à 0.5 est recommendée
void suivreLigne(float vitesse);
//détection d'une ligne
bool detecterLigne();
//trouve et suis une ligne
bool traquerLigne(float vitesse);


#endif