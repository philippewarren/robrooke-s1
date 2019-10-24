#include "conversions.h"

const double CLICS_PAR_CM = 3200/(2.54*3*PI);
const float tensionArduino = 5.0;
const uint16_t entreeAnalogiqueMax = 1023;
const float diaRoue = 7.6;
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
  float tension = (float)((tensionArduino/entreeAnalogiqueMax)*(entreeAnalogique));

  return tension;
}

float tensionEnDistance(float tension)
{
  if (tension<=0.3) return 0;
  float distanceEnCM = 29.988 * pow(tension, -1.173);
  return distanceEnCM;
}

void rgbEnHsl(uint16_t tableauRGB[4])
{
  uint16_t etendue = BORNES_COULEUR[1]-BORNES_COULEUR[0];
  
  // float rouge = tableauRGB[0]/255.0;
  // float vert = tableauRGB[1]/255.0;
  // float bleu = tableauRGB[2]/255.0;
  float rouge = ((float)tableauRGB[0]-BORNES_COULEUR[0])/(etendue);
  float vert = ((float)tableauRGB[1]-BORNES_COULEUR[0])/(etendue);
  float bleu = ((float)tableauRGB[2]-BORNES_COULEUR[0])/(etendue);
  float sansCouleur = tableauRGB[3];
  
  {
    Serial.print(255*rouge);
    Serial.print('\t');
    Serial.print(255*vert);
    Serial.print('\t');
    Serial.print(255*bleu);
    Serial.print('\t');
    Serial.println();
  }

  float Cmax = max(rouge, max(vert, bleu));
  float Cmin = min(rouge, min(vert, bleu));
  float delta = Cmax-Cmin;
  float preS;

  uint16_t H, S, L;

  if (delta==0) H = 0;
  else if (Cmax==rouge) H = (uint16_t)(60*(((vert-bleu)/delta) + (vert<bleu ? 6 : 0)));
  else if (Cmax==vert) H = (uint16_t)(60*(((bleu-rouge)/delta) + 2));
  else if (Cmax==bleu) H = (uint16_t)(60*(((rouge-vert)/delta) + 4));

  preS = (delta==0) ? 0 : delta/(1-fabs(2*((Cmax+Cmin)/2)-1));
  S = /*(100*preS>SEUIL_NOIR) ? */(uint16_t)(100*pow(preS, 0.5)) /*: (uint16_t)(100*preS)*/;

  L = (uint16_t)(100*(Cmax+Cmin)/2);
  // L = (uint16_t)(100*((sansCouleur-3*BORNES_COULEUR[0])/(3.0*etendue)));
 

  tableauRGB[0] = H;
  tableauRGB[1] = S;
  tableauRGB[2] = L;
   
  return;
}