#ifndef CAPTEUR_IR_H
#define CAPTEUR_IR_H

#include <LibRobus.h>
#include "operations_generales.h"
#include "conversions.h"

//Utilisée pour lire une valeur de distance en cm du capteur IR (index entre 0 et 3), en prenant amplitude*2-1 mesures
float lireDistanceIR(uint8_t capteur, uint8_t amplitude = 3);



#endif