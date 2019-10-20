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

void rgbEnHsl(uint16_t tableau[4])
{
  float rouge = 256*tableau[0]/tableau[4];
  float vert = 256*tableau[1]/tableau[4];
  float bleu = 256*tableau[2]/tableau[4];

  float Cmax = max(rouge, max(vert, bleu));
  float Cmin = min(rouge, min(vert, bleu));
  float delta = Cmax-Cmin;

  uint16_t H = 60, S, L;

  if (delta==0) H *= 0;
  else if (Cmax==rouge) H *= (uint16_t)(((uint16_t)((vert-bleu)/delta)) % 6);
  else if (Cmax==vert) H *= (uint16_t)(((uint16_t)((bleu-rouge)/delta)) + 2);
  else if (Cmax==bleu) H *= (uint16_t)(((uint16_t)((rouge-vert)/delta)) + 4);

  S = (delta==0) ? 0 : (uint16_t)(100*delta/(1-abs(2*((Cmax+Cmin)/2)-1)));

  L = (uint16_t)(100*(Cmax+Cmin)/2);

  tableau[0] = H;
  tableau[1] = S;
  tableau[2] = L;
   
  return;
}