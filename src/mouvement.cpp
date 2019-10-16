#include "mouvement.h"

void resetDeuxEncodeurs()
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  return;
}

void changerVitesseMoteur(uint8_t moteur, float nouvelleVitesse)
{
  static float derniereVitesse[] = {0,0};

  if ((derniereVitesse[moteur]*nouvelleVitesse)<0)
  {
    MOTOR_SetSpeed(moteur, 0);
    delay(50);
  }

  MOTOR_SetSpeed(moteur, nouvelleVitesse);
  derniereVitesse[moteur] = nouvelleVitesse;
  
  return;
}

void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD = 200)
{   
    if (vitesseD==200) vitesseD=vitesseG;
    changerVitesseMoteur(0,vitesseG);
    changerVitesseMoteur(1,vitesseD);
    return;
}

void arreterDeuxMoteurs()
{
  changerVitesseDeuxMoteurs(0);
  return;
}