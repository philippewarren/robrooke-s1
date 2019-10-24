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

void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD = 200.0)
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

//PI retourne différence droite-gauche
float partielIntegralDerive(bool reset = 0)
{
  float kp = 0.2;
  float ki = 0.005;
  float kd = 0;
  static int timer = micros();
  static float integrale = 0;
  static float retour = 0;
  if (reset)
  {
    timer = micros();
    integrale = 0;
    retour = 0;
  }
  float deltaT = (float)(micros()-timer)/1000000;
  float diffdist = ENCODER_ReadReset(0)-ENCODER_ReadReset(1);
  float partiel = kp*diffdist / deltaT;
  integrale += ki*diffdist;
  float derive = kd*diffdist*deltaT;
  timer = micros();
  if(!reset)
  {
    Serial.println("iteration");
  Serial.println(partiel);
  Serial.println(integrale);
  Serial.println(derive);
  }
  retour += (partiel + integrale + derive)/1000;
  return retour;


}
//mouvement non bloquant
bool avancerDroit(float vitesse, float distance);