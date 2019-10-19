#include "conversions.h"

const double CLICS_PAR_CM = 3200/(2.54*3*PI);
const float tensionArduino = 5.0;
const uint16_t entreeAnalogiqueMax = 1023;
const float diaRoue = 7.6;
float largeurEss;

double clicsEnCm(long nbClics)
{
  return nbClics/CLICS_PAR_CM;
}

long long cmEnClics(float nbCm)
{
  return (long long)(nbCm*CLICS_PAR_CM);
}

float entreeAnalogiqueEnTension(uint16_t entreeAnalogique)
{
  return (float)((tensionArduino/entreeAnalogiqueMax)*(entreeAnalogique));
}

float tensionEnDistance(float tension)
{
  float distanceEnCM;
  distanceEnCM = 29.988 * pow(tension, -1.173);
  return distanceEnCM;
}