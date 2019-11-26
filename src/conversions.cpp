#include "conversions.h"

const double CLICS_PAR_CM = 3200/(2.54*3*PI);
const float TENSION_ARDUINO = 5.0;
const uint16_t ENTREE_ANALOGIQUE_MAX = 1023;
const float DIAMETRE_ROUE = 7.6;
float largeurEss;

extern const uint16_t BORNES_COULEUR[];

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
  float tension = (float)((TENSION_ARDUINO/ENTREE_ANALOGIQUE_MAX)*(entreeAnalogique));

  return tension;
}

float tensionEnDistance(float tension)
{
  if (tension<=0.3) return 0;
  float distanceEnCM = 29.988 * pow(tension, -1.173);
  return distanceEnCM;
}

