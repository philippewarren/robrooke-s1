#include "capteur_couleur.h"

Adafruit_TCS34725 CapteurCouleur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void initialiserCapteur()
{
    CapteurCouleur.begin();

    return;
}

void lireCapteurCouleur(uint8_t numero, int tableau[])
{    
    
}