#ifndef DEPLACEMENT
#define DEPLACEMENT

#include <Arduino.h>

#include <LibRobus.h>


//Adapte la vitesse du moteur droit à celle du moteur gauche. La vitesse du moteur gauche doit être spécifié, si ce n'est pas le cas la derniere vitesse utilisée dans la fonction sera utilisée à nouveau.
void syncroMoteur(const float nouvelleVitesse = -1000);

#endif