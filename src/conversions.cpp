#include "conversions.h"

const double CLICS_PAR_CM = 3200/(2.54*3*PI);
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