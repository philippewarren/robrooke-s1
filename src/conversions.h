#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include <LibRobus.h>

extern const double CLICS_PAR_CM;
//diametre de la roue en cm
extern const float diaRoue;
//distance entre les roues en cm
extern float largeurEss;

//Convertit un nombre de clics d'encodeur en distance (en cm)
double clicsEnCm(long);

//Convertit une distance (en cm) en nombre de clics d'encodeur
long long cmEnClics(float);


#endif