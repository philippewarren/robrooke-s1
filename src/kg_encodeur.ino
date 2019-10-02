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

namespace rotation
{
/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces

  
  const uint8_t gauche = 0;
  const uint8_t droite = 1;

  const float vitesseRotation = 0.2;
  float correction = 1.0;
  const float diaRoue = 7.62;
  const float largeurEss = 19;
  const float largeurParc = 0.45;

  int pulse180 = 0;
  int pulseMin = 0;
  int pulseMax = 0;
  float rappRot = 0;

  int pulseD = 0;
  int pulseG = 0;



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

///calcul des constantes
void calculPulse180()
{
  pulse180 = largeurParc*1600/largeurEss;
}
void calculPulseMin()
{
  pulseMin = (largeurParc - largeurEss) * 400 / diaRoue;
}
void calculPulseMax()
{
  pulseMax = (largeurParc + largeurEss) * 400 / diaRoue;
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
///rotation 180
void DemiTour()
{
  pulseD = 0;
  pulseG = 0;
  encReset();
  MOTOR_SetSpeed(droite,vitesseRotation);
  MOTOR_SetSpeed(gauche,-vitesseRotation);
  delay(100);
  correction = float(readResetKeepDroit())/float(readResetKeepGauche());
  MOTOR_SetSpeed(droite,vitesseRotation/correction);
  while (pulseD < pulse180)
  {
    correction = float(readResetKeepDroit())*correction/float(readResetKeepGauche());
    MOTOR_SetSpeed(droite,vitesseRotation/correction);
    delay(100);
  }
}



}


/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

/*void setup(){
  BoardInit();
  rotation::initRot;
  rotation::DemiTour;
}*/


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

//void loop() {
//}
