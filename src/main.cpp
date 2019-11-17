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

//Dépose une lettre
bool deposerLettrePoste()
{
  bool suivant = false;
  baisserBras();
  ouvrirPince();
  eteindreDELCouleur();
  suivant = estLettreSuivant();
  leverBras();

  return suivant;
}

//Ramasse une lettre. S'il n'y a pas de lettre, renvoie -1 et éteint les DEL. S'il échoue à ramasser la lettre,
//renvoie -2 et éteint les DEL. Sinon, renvoie la couleur de la lettre et allume la DEL de la couleur correspondante.
int ramasserLettre()
{
  baisserBras();
  if(estLettrePince())
  {
    fermerPince();
    leverBras();
    if(estLettrePince())  return allumerDELCouleur(obtenirCouleurLettre());
    else
    {
      ouvrirPince();
      return allumerDELCouleur(-2);
    }
  }
  else
  {
    leverBras();
    return allumerDELCouleur(-1);
  }
}

//Ouvre la pince, puis ramasse les lettres, retourne le resultat de ramasserLettre()
int deposerEtReprendreLettre()
{
  ouvrirPince();
  return ramasserLettre();
}

void actionPoste()
{
  ouvrirPince();
  avancerDroitBloque(0.3,3);
  traquerLigneBloque(0.3);
  //baisser Bras
  fermerPince();
  //monter Bras
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
    fermerPince();
    allerVers(i);
    actionPoste();
    allerVers(0);
    ouvrirPince();
  }
}

void testCouleur()
{
  int noeud = -1;
  while (noeud == -1)
  {
    noeud = convertirCouleurNoeud(obtenirCouleurLettre());
  }
  fermerPince();
  allerVers(noeud);
  actionPoste();
  allerVers(0);
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
  // testDeplacement();
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop()
{
  // debugCapteurCouleur();
  // loopAjustementServo(BRAS);
 ramasserLettre();
 delay(1000);
 deposerLettrePoste();
 delay(1000);
// debugCapteurIR();
  // debugEstLettre();
}
