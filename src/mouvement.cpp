#include "mouvement.h"
#include "math.h"

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

void syncroroue(float vitesse, float multiDroit = 1, bool reset = 0)
{
  static float correction = 1;
  if (reset)
  {
    correction = 1;
    resetDeuxEncodeurs();
  }
  if (ENCODER_Read(0) != 0 && ENCODER_Read(1) != 0)
    correction *= ENCODER_ReadReset(0) / (ENCODER_ReadReset(1) * multiDroit);
  if (correction * multiDroit < 0)
  {
    correction *= -1;
  }

  bool neg = false;
  if (correction < 0)
  {
    correction *= -1;
    neg = true;
  }

  float vitesseD = vitesse * sqrt(correction);
  float vitesseG = vitesse / sqrt(correction);

  if (neg)vitesseG *= -1;

  /*if (vitesseD < 0.15 && vitesseD > 0) vitesseD = 0.15;
  if (vitesseD > -0.15 && vitesseD < 0) vitesseD = -0.15;

  if (vitesseG < 0.15 && vitesseG > 0) vitesseG = 0.15;
  if (vitesseG > -0.15 && vitesseG < 0) vitesseG = -0.15;*/

  changerVitesseDeuxMoteurs(vitesseG, vitesseD);
}
//mouvement non bloquant
bool avancerDroit(float vitesse, float distance)
{
  static float distanceParcourue = 0;
  static long timer = millis();
  static bool reset = true;
  static bool resetEnc = false;
  static float ancEnc = 0;

  if (distance == 0)
    return true;
  else
  {
    if (vitesse*distance < 0)vitesse *= -1;

    if(Bob == 'A') distance /= 1.175;
    else distance /= 1.05;

    float enc = clicsEnCm(ENCODER_Read(0));

    if (reset)
    {
      timer = millis();
      ancEnc = clicsEnCm(ENCODER_Read(0));
      reset = false;
    }

    distanceParcourue += enc - ancEnc;

    if (resetEnc)
    {
      distanceParcourue += ancEnc;
      resetEnc = false;
    }

    ancEnc = enc;


    if ((distanceParcourue >= distance && distance > 0)||(distanceParcourue <= distance && distance < 0))
    {
      distanceParcourue = 0;
      syncroroue(0, 1, true);
      return true;
    }
    else
    {
      if (millis() - timer > 50)
      {
        syncroroue(vitesse);
        resetEnc = true;
        timer = millis();
      }
      return false;
    }
  }
}

bool tourner(float vitesse, float angle)
{
  static float distanceParcourue = 0;
  static long timer = millis();
  static bool reset = true;
  static bool resetEnc = false;
  static float ancEnc = 0;

  float distance = (19 * 3.14160) / 360 * angle;
  if(Bob == 'A') distance /= 1.175;
  else distance /= 1.05;
  float enc = clicsEnCm(ENCODER_Read(1));

  if (reset)
  {
    distanceParcourue = 0;
    timer = millis();
    ancEnc = clicsEnCm(ENCODER_Read(1));
    reset = false;
  }

  distanceParcourue += enc - ancEnc;
  if (angle * vitesse < 0)
    vitesse *= -1;

  if (resetEnc)
  {
    distanceParcourue += ancEnc;
    resetEnc = false;
  }

  ancEnc = enc;


  if ((distanceParcourue >= distance && distance > 0)||(distanceParcourue <= distance && distance < 0))
  {
    reset = true;
    distanceParcourue = 0;
    syncroroue(0, 1, true);
    return true;
  }
  else
  {
    if (millis() - timer > 50)
    {
      syncroroue(vitesse, -1.0);
      resetEnc = true;
      timer = millis();
    }
    return false;
  }
}

//mouvement bloquant
bool avancerDroitBloque(float vitesse, float distance)
{
  float distanceParcourue = 0;
  bool fin = false;

  distance = cmEnClics(distance);
  if(Bob == 'A') distance /= 1;
  else distance /= 1;
  resetDeuxEncodeurs();
  syncroroue (vitesse,1,true);
  if (vitesse * distance < 0)vitesse *= -1;

  while (!fin)
  {
    delay(50);
    distanceParcourue += ENCODER_Read(0);
    syncroroue(vitesse);
    fin = (distanceParcourue >= distance && distance > 0)||(distanceParcourue <= distance && distance < 0);
  }
  syncroroue (0,1,true);
  return true;
}

bool tournerBloque(float vitesse, float angle)
{
  float distanceParcourue = 0;
  bool fin = false;

  if(Bob == 'A') angle -
  3;
  else angle /= 1;
  float distance = cmEnClics((19 * 3.14160) / 360 * angle);
  resetDeuxEncodeurs();
  syncroroue (vitesse,-1,true);
  if (vitesse * angle < 0)vitesse *= -1;

  while (!fin)
  {
    delay(30);
    distanceParcourue += ENCODER_Read(1);
    syncroroue(vitesse,-1);
    fin = (distanceParcourue >= distance && distance > 0)||(distanceParcourue <= distance && distance < 0);
  }
  syncroroue (0,1,true);
  return true;
}
