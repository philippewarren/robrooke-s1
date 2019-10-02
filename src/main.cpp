/*
Projet: Défi du parcours
Equipe: P-28
Auteurs: Philippe Warren, Keven Gagnon, William Bruneau, Pénélope Montminy, Camille Durivage-Guertin, Gabriel Doré, Philippe Gadeyne, Antoine Duguay 
Description: Breve description du script
Date: 29-septembre-2019//
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h>   // Essentielle pour utiliser RobUS
#include <Arduino.h>    // Essentielle pour certaines commandes Arduino
#include <pw_ligne_droite.h>
#include <EEPROM.h>
//#include <kg_encodeur.h>
//#include <kg_rotation.h>

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces

enum RobUS {A,B,I};
RobUS BOB = I;
char Bob = 'I';

/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
 // rotation::initRot();
  Serial.println("Ceci est le test setup");
 // EEPROM.update(0,'A');
  if (EEPROM.read(0)=='A') {BOB = A; Bob = 'A';}
  if (EEPROM.read(0)=='B') {BOB = B; Bob = 'B';}
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {

  Serial.print(BOB);
  Serial.print(Bob);
  if (ROBUS_IsBumper(3))
  {
    Serial.println("Ceci est le test isBumper(3)");
    avancerDroit(100);
  }

   if (ROBUS_IsBumper(2))
  {
    Serial.println("Ceci est le test isBumper(2)");
    
  }

  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
}