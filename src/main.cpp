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
#include "transfert.h"

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

void actionPoste()
{
  fermerPince();
  avancerDroitBloque(0.3,3);
  traquerLigneBloque(0.3);
  ouvrirPince();
  tournerBloque(0.2,180);
  traquerLigneBloque(0.3);
  poserEtat(-1,obtenirOrientation()+180);
}
void testDeplacement()
{
  for(int i = 0; i<6;i++)
  {
    allerVers(i);
    for(int j = (i+1);j<7;j++)
    {
      allerVers(j);
      allerVers(i);
    }
  }
  allerVers(0);
}
void testPoste()
{
  for (int i = 3; i<7; i++)
  {
    allerVers(i);
    actionPoste();
    allerVers(0);
  }
}





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
  poserEtat(0,180);
  // testPoste();
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop()
{
  if(loopEstCliqueEtRelache(0)) ouvrirPince();
  if(loopEstCliqueEtRelache(1)) fermerPince();
}
