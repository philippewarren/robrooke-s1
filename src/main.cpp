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

//#include "init_robot.h"
#include <Arduino.h>
//#include <LibRobus.h>
//#include "interactions.h"
//#include "suiveur_ligne.h"
#include "transfer.h"

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
// -> Generalement on y initilise les varibbles globales


bool start = false;
int taille = 0;
int tableau[TAILLE_MAX][TAILLE_MAX];
int ligne [TAILLE_MAX];

void test_trajet(int d, int f)
{
  int out[TAILLE_MAX];
  Serial.print("trajet de ");
  Serial.print(d);
  Serial.print(" a ");
  Serial.print(f);
  Serial.print('\n');
  calculer_trajet(d,f,out);
  afficher_trajet(out);
}

void setup()
{
  Serial.begin(9600);
  test_trajet(0,4);
  test_trajet(4,6);
  test_trajet(5,0);
  test_trajet(0,10);
  test_trajet(1,2);

  
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop()
{
  //if (arretUrgence) loopUrgence();
 // else loopNormal();


}
