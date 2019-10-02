#include <LibRobus.h>
#include <EEPROM.h>
#include <fonctions_generales.h>

char Robot = 'I';

void determinerRobot()
{
    Robot = EEPROM.read(0);
}

double clicsEnCm(long nbClics)
{
  return nbClics/CLICS_PAR_CM;
}

long long cmEnClics(float nbCm)
{
  return (long long)(nbCm*CLICS_PAR_CM);
}

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

void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD)
{
  changerVitesseMoteur(0,vitesseG);
  changerVitesseMoteur(1,vitesseD);
  return;
}

void arreterDeuxMoteurs()
{
  changerVitesseDeuxMoteurs(0,0);
  return;
}