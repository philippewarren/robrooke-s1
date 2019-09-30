/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <Arduino.h>




/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces

  
  const uint8_t gauche = 0;
  const uint8_t droite = 1;

  const float vitesseRotation = 0.5;
  float correction = 1.0;
  const float diaRoue = 7.6;
  const float largeurEss = 18.2;
  const float largeurParc = 45;

  long pulse180 = 0;
  long pulseMin = 0;
  long pulseMax = 0;
  float rappRot = 0;

  int pulseD = 0;
  int pulseG = 0;



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

///calcul des constantes
void calculPulse180()
{
  pulse180 = largeurEss*1600/diaRoue;
}
void calculPulseMin()
{
  pulseMin = (largeurParc - largeurEss) * 200 / diaRoue;
}
void calculPulseMax()
{
  pulseMax = (largeurParc + largeurEss) * 200 / diaRoue;
}

///initialisation des constantes
void initRot()
{
  calculPulse180();
  calculPulseMax();
  calculPulseMin();
  float pMax = pulseMax;
  float pMin = pulseMin;
  rappRot = pMin / pMax;
}
///lecture d'encodeur avec stockage
int readResetKeepDroit()
{
  int out = ENCODER_ReadReset(droite);
  pulseD += out;
  return out;
}
int readResetKeepGauche()
{
  int out = ENCODER_ReadReset(gauche);
  pulseG += out;
  return out;
}
void encReset()
{
  ENCODER_ReadReset(gauche);
  ENCODER_ReadReset(droite);
}
///rotation 180                                 BUG avec correction possiblement lié à readResetKeep
void DemiTour()
{
  pulseD = 0;
  pulseG = 0;
  encReset();
  MOTOR_SetSpeed(droite,vitesseRotation);
  MOTOR_SetSpeed(gauche,-vitesseRotation);
  delay(100);
  correction = -float(readResetKeepDroit())/float(readResetKeepGauche());
  MOTOR_SetSpeed(gauche,vitesseRotation/correction);
  while (pulseD > -pulse180)
  {
    delay(10);
    correction = float(readResetKeepDroit())/(-float(readResetKeepGauche())/correction);
    MOTOR_SetSpeed(gauche,-vitesseRotation*correction);
  }
  MOTOR_SetSpeed(droite,0);
  MOTOR_SetSpeed(gauche,0);
}

void Rot451Roue(int Nbr45 = 1 , bool dirGauche = false)
{
  int roue = gauche;
  if (dirGauche) roue = droite;
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
  long clic = pulse180 / 2 * Nbr45;
  MOTOR_SetSpeed(roue,vitesseRotation);
  long pulseTotal = 0;
  while (pulseTotal < clic)
  {
    delay(30);
    pulseTotal -= ENCODER_ReadReset(roue);
  }
  MOTOR_SetSpeed(roue,0);
  
}

//Plan A (45)

void Rot452Roue(int Nbr45 = 1 , bool dirGauche = false)
{
  long nbpulses = 0;
  long nbpulseM = 0;
  //Assignation des roues
  int Rmax = gauche;
  int Rmin = droite;

  if (dirGauche)
  {
    Rmax = droite;
    Rmin = gauche;
  }

  //Rouler
  MOTOR_SetSpeed(Rmax, vitesseRotation);
  MOTOR_SetSpeed(Rmin, vitesseRotation*rappRot);

  while(nbpulses < pulseMin && nbpulseM < pulseMax)
  {
    delay(30);

    int pmin = ENCODER_ReadReset(Rmin);
    int pmax = ENCODER_ReadReset(Rmax);
    nbpulses -= pmin;
    nbpulseM -= pmax;
    if (nbpulses > pulseMin)MOTOR_SetSpeed(Rmin,0);
    if (nbpulseM > pulseMax)MOTOR_SetSpeed(Rmax,0);

   /* correction =pmin /ENCODER_ReadReset(Rmax)*correction/rappRot;
    MOTOR_SetSpeed(Rmax,vitesseRotation*correction);*/
  }
MOTOR_SetSpeed(droite,0);
MOTOR_SetSpeed(gauche,0);
}


/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
  initRot();
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  if(ROBUS_IsBumper(3))
  {
  DemiTour();
  }
  if(ROBUS_IsBumper(1))
  {
    delay(1000);
    Rot452Roue(1);
    delay(1000);
  }
  if(ROBUS_IsBumper(0))
  {
    delay(1000);
    Rot452Roue(1,1);
    delay(1000);
  }
}