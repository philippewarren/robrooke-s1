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
#include "loop_normal.h"
#include "loop_urgence.h"

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */




/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les variables globales



void setup()
{
  initialiserBob();
  pinMode(OUTPUT,12);
  digitalWrite(12,HIGH);
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop()
{
  // if (arretUrgence) /*loopUrgence()*/;
  // else loopNormal();
  //pour ajouter des fonction à la boucle, veuillez modifier la boucle normale (loop_normal.cpp)

  // debugCapteurCouleur();
  // changerAngleServo(PINCE, 45, false);
  // delay(1000);
  // changerAngleServo(PINCE, 45, false);
  // delay(1000);
  // changerAngleServo(PINCE, 0, true);
  // delay(2000);

  // loopAjustementServo(PINCE);

  // if(loopEstCliqueEtRelache(0)) ouvrirPince();
  // if(loopEstCliqueEtRelache(1)) fermerPince();

}
