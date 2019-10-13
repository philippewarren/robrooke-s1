#include "mouvement.h"



void resetDeuxEncodeurs()
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  return;
}

void changerVitesseMoteur(uint8_t moteur, float nouvelleVitesse)
{
  /*int32_t ancienneVitesseEnClics = ENCODER_Read(moteur);
  if ((ancienneVitesseEnClics<0 && nouvelleVitesse>0) || (ancienneVitesseEnClics>0 && nouvelleVitesse<0) || ancienneVitesseEnClics==0)
  {
    MOTOR_SetSpeed(moteur, 0);
    delay(25);
    MOTOR_SetSpeed(moteur, nouvelleVitesse);
  }
  else*/ MOTOR_SetSpeed(moteur, nouvelleVitesse);
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