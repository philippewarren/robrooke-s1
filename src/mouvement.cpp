#include "mouvement.h"

void resetDeuxEncodeurs()
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  return;
}

//NE JAMAIS UTILISER
bool estChangeDeDirection(uint8_t moteur, float nouvelleVitesse)
{
  static float derniereVitesse[] = {0,0};

  bool resultat = 0;

  if ((derniereVitesse[moteur]*nouvelleVitesse)<0) resultat=true;
  derniereVitesse[moteur] = nouvelleVitesse;

  return resultat;
}

void changerVitesseMoteur(uint8_t moteur, float nouvelleVitesse)
{
  if (estChangeDeDirection(moteur, nouvelleVitesse))
  {
    MOTOR_SetSpeed(moteur, 0);
    delay(50);
  }

  MOTOR_SetSpeed(moteur, nouvelleVitesse);

  return;
}

void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD = 200)
{   
  if (vitesseD==200) vitesseD=vitesseG;
  
  bool changeG = estChangeDeDirection(0, vitesseG);
  bool changeD = estChangeDeDirection(1, vitesseD);

  if (changeG || changeD)
  {
    arreterDeuxMoteurs();
    delay(50);
  }

  MOTOR_SetSpeed(0,vitesseG);
  MOTOR_SetSpeed(1,vitesseD);
  
  return;
}

void arreterDeuxMoteurs()
{
  changerVitesseDeuxMoteurs(0);
  return;
}