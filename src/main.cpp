/*
Projet: Parcours du combattant
Equipe: P-28
Auteurs: Philippe Warren, Keven Gagnon, William Bruneau, Pénélope Montminy, Camille Durivage-Guertin, Gabriel Doré, Philippe Gadeyne, Antoine Duguay 
Description: Lance le script pour l'épreuve du combattant
Date: 29-septembre-2019//
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include "init_robot.h"

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces

//float array[1000][1000];
  unsigned int donnees[1500];
  unsigned int donneesMoyenneMobile[1500];
  int index = 0;
  bool statut = false;

/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

void demiTour()
{
  const int DT = 5; //delta time?
  const float PULSE = 133.333;//nombre de pulse par cm
  const float EspaceRoue = 18.75;//distance entre chaque roue en cm
  const float DISTANCE = 3.141592654 * EspaceRoue*PULSE/2;//distance en pulsation pour un demi tour
  const bool gauche = 0;
  const bool droit = 1;
  float v_initiale = 0.22; //vitesse initiale
  float e_vitesse = 0;
  float kp = 0;
  //offset de bobB
  float offset = -1.4*PULSE;
  //offset de bobA
  //if (robot == 'A')offset = -1*PULSE;

  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
  delay(500);//temps de repos pour discipation du champ magnétique des encodeurs
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  while(ENCODER_Read(gauche)<2*(DISTANCE+offset))
  {
    MOTOR_SetSpeed(droit,-1*v_initiale+kp);
    MOTOR_SetSpeed(gauche, v_initiale);
    //fonction pid
    delay(DT);
  e_vitesse =((ENCODER_Read(droit))/DISTANCE) -((ENCODER_Read(gauche))/DISTANCE)/DT;
  kp = e_vitesse*v_initiale*0.2;
    //Serial.print("Encodeur : ");
    //Serial.print(ENCODER_Read(0));
    //Serial.print(";");
    Serial.println(ROBUS_ReadIR(0));
  }
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
  delay(500);//temps de repos pour discipation du champ magnétique des encodeurs
  ENCODER_Reset(0);
  ENCODER_Reset(1);

}

void faireMoyenneMobile(int nbrItems)
{
  donneesMoyenneMobile[0] = donnees[0];
  for (int i = 1; i < nbrItems - 1; i++)
  {
    donneesMoyenneMobile[i] = (donnees[i-1] + donnees[i+1])/2.0;
  }
  donnees[nbrItems - 1] = donnees[nbrItems - 1];
  

}

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup()
{
  initialiserBob();
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop()
{


    // if (ROBUS_IsBumper(3))
    // {
    //   demiTour();
    // }

    // if (ROBUS_IsBumper(2))
    // {
    //   MOTOR_SetSpeed(0,0.5);
    //   MOTOR_SetSpeed(1,0.5);
    //   while (true)
    //   {
    //     Serial.println(ROBUS_ReadIR(0));

    //     if (ROBUS_IsBumper(3)) break;
    //   }
    // }
    if(loopEstCliqueEtRelache(3))
    {
      statut = true;

    }
    if(statut)
    {
      MOTOR_SetSpeed(0,0.25);
      MOTOR_SetSpeed(1,-0.25);
      donnees[index] = ROBUS_ReadIR(0);
      index++;
    }
    if(ENCODER_Read(0) > 8500)
    {
      MOTOR_SetSpeed(0,0);
      MOTOR_SetSpeed(1,0);
      Serial.println("Termine");
      Serial.println(index);
      faireMoyenneMobile(index);
      for (int i = 0; i < index; i++)
      {
        Serial.println(donneesMoyenneMobile[i]);
      }
      while(true)
      {
        delay(10);
      }
    }

  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
}
