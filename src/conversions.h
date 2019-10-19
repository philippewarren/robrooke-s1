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

//Convertit une entree analogique (0 à 1023) en tension (0.0 à 5.0 V)
float entreeAnalogiqueEnTension(uint16_t entreeAnalogique);

//Convertit une mesure de tension provenant d'un capteur infrarouge en distance en cm
float tensionEnDistance(float tension);


#endif