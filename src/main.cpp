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

#include <LibRobus.h>   // Essentielle pour utiliser RobUS
#include <Arduino.h>    // Essentielle pour certaines commandes Arduino
//#include <EEPROM.h>

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces

//float array[1000][1000];

/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

void demiTour()
{
  const int DT = 5;
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

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
  //robotInit();
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop()
{

    if (ROBUS_IsBumper(3))
    {
        demiTour();
    }



  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
}
