/*
Projet: PIRUS Robrooke
Equipe: P-28
Auteurs: Philippe Warren, Keven Gagnon, William Bruneau, Pénélope Montminy, Camille Durivage-Guertin, Gabriel Doré, Philippe Gadeyne, Antoine Duguay 
Description: Lance le loop principal du robot facteur, et contient les fonctions les plus high-level utilisées pour PIRUS
Date: 29-septembre-2019//
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include "init_robot.h"
#include "servomoteur.h"
#include "transfert.h"

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
bool posteRouge = false;
bool posteBleu = false;
bool posteJaune = false;
bool posteVert = false;
bool posteRouge2 = false;
bool posteBleu2 = false;
bool posteJaune2 = false;
bool posteVert2 = false;
int lettreEnMain = -1; //-1 si vide ou couleur
int essaiDist = 0;
volatile int bouton = 0;
volatile int itBouton = 0;

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
  leverBrasDeplacement();

  return suivant;
}

//Ramasse une lettre. S'il n'y a pas de lettre, renvoie -1 et éteint les DEL. S'il échoue à ramasser la lettre,
//renvoie -2 et éteint les DEL. Sinon, renvoie la couleur de la lettre et allume la DEL de la couleur correspondante.
int ramasserLettre()
{
  // leverBras();
  ouvrirPince();
  baisserBras();
  if(estLettrePince())
  {
    fermerPince();
    leverBrasDeplacement();
    if(estLettrePince())  return allumerDELCouleur(obtenirCouleurLettre());
    else return allumerDELCouleur(-2);
  }
  else
  {
    leverBrasDeplacement();
    return allumerDELCouleur(-1);
  }
}

void actionPoste()
{
  if(deposerLettrePoste())
  {
    int couleur = lettreEnMain;
    avancerDroitBloque(0.2,3);
    traquerLigneBloque(0.2);
    lettreEnMain = ramasserLettre();
    if(lettreEnMain == -2)lettreEnMain = ramasserLettre();
    tournerBloque(0.2,180);
    traquerLigneBloque(0.3);
    if(lettreEnMain == couleur)
    {
      tournerBloque(0.2,180);
      deposerLettrePoste();
      tournerBloque(0.2,180);
      lettreEnMain = -1;
    }
    poserEtat(-1,obtenirOrientation()+180);
  }
  else
  {
    lettreEnMain = -1;
  }
  
}

void routineDistribution()
{
  allerVers(0);
  if(obtenirOrientation() == 180)tournerBloque(0.2,180);
  
  if(posteJaune && posteRouge && posteVert && posteBleu)
  {
    posteBleu = false;
    posteJaune = false;
    posteVert = false;
    posteRouge = false;
  }
  bool fin = false;
  if(!posteVert && posteBleu && posteRouge && posteJaune)
  {
    tournerBloque(0.2,180);
    lettreEnMain = ramasserLettre();
    if (lettreEnMain == -2)lettreEnMain =ramasserLettre();
    posteVert = true;
    fin = true;
  }
  if(!posteJaune)
  {
    lettreEnMain = ramasserLettre();
    if (lettreEnMain == -2)lettreEnMain =ramasserLettre();
    if (lettreEnMain >= 0)
    {
      fin = true;
      tournerBloque(0.2,180);
    }
    posteJaune = true;
  }
  if(!fin)
  {
    avancerDroitBloque(0.2,3);
    traquerLigneBloque(0.3);
    if(lettreEnMain < 0 && !posteRouge)
    {
      lettreEnMain = ramasserLettre();
      if (lettreEnMain == -2)lettreEnMain =ramasserLettre();
      posteRouge = true;
    }
    tournerBloque(0.2,180);
    if(lettreEnMain < 0 && !posteBleu)
    {
      lettreEnMain = ramasserLettre();
      if (lettreEnMain == -2)lettreEnMain =ramasserLettre();        
      posteBleu = true;
    }
    avancerDroitBloque(0.2,3);
    traquerLigneBloque(0.3);
    if(lettreEnMain < 0 && !posteVert)
    {
      lettreEnMain = ramasserLettre();
      if (lettreEnMain == -2)lettreEnMain =ramasserLettre();
      posteVert = true;
    }
    
  }
  poserEtat(0,180);
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

void demoAudit2()
{
  traquerLigneBloque(0.2);
  while (lettreEnMain < 0)
  {
    lettreEnMain = ramasserLettre();
  }
  if(bouton == 1)bouton = 2;
  avancerDroitBloque(0.2,3);
  traquerLigneBloque(0.3);
  if (lettreEnMain == ROUGE)
  {
    deposerLettrePoste();
    tournerBloque(0.2,180);
  }
  else
  {
    avancerDroitBloque(0.2,3);
    traquerLigneBloque(0.2);
    deposerLettrePoste();
    tournerBloque(0.2,180);
    avancerDroitBloque(0.2,3);
    traquerLigneBloque(0.2);
  }
  avancerDroitBloque(0.2,3);
  traquerLigneBloque(0.2);
  avancerDroitBloque(0.2,10);
  tournerBloque(0.2,180);
  lettreEnMain = -1;
}

void fctBouton()
{
  if(bouton == 0)
    bouton = 1;
  if(bouton == 2)
    bouton = 3;
}

//Initialise le port pour l'interrupt et l'attache
void initialiserInterrupt()
{
  const byte PORT_INTERRUPT = 2;

  pinMode(PORT_INTERRUPT, INPUT);
  attachInterrupt(digitalPinToInterrupt(PORT_INTERRUPT), fctBouton, HIGH);
}

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les variables globales



void setup()
{
  initialiserRobot();
  initialiserInterrupt();
  Serial.println("##Reboot##");
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"
int tableau3[8];
void loop()
{
  if(bouton == 1)
  {
    eteindreDEL(0);
    allumerDEL(1);
    traquerLigneBloque(0.2);
    poserEtat(0,180);
    bouton = 2;
  }
  else if (bouton == 3)
  {
    eteindreDEL(0);
    allumerDEL(2);
    arreterDeuxMoteurs();
    bouton = 0;
  }
  else if (bouton == 2)
  {
    eteindreDEL(0);
    allumerDEL(3);
    if(lettreEnMain>=0)
    {
      essaiDist = 0;
      if (lettreEnMain == ROUGE) posteRouge2 = true;
      if (lettreEnMain == JAUNE) posteJaune2 = true;
      if (lettreEnMain == VERT) posteVert2 = true;
      if (lettreEnMain == BLEU) posteBleu2 = true;
      allerVers(convertirCouleurNoeud(lettreEnMain));
      actionPoste();
    }
    else if(essaiDist < 2)
    {
      essaiDist ++;
      Serial.println("distribution");
      routineDistribution();
    }
    else
    {
      if (!posteRouge2)
      {
        allerVers(convertirCouleurNoeud(ROUGE));
        actionPoste();
        posteRouge2 = true;
      }
      else if(!posteBleu2)
      {
        allerVers(convertirCouleurNoeud(BLEU));
        actionPoste();
        posteBleu2 = true;
      }
      else if(!posteJaune2)
      {
        allerVers(convertirCouleurNoeud(JAUNE));
        actionPoste();        
        posteJaune2 = true;
      }
      else if(!posteVert2)
      {
        allerVers(convertirCouleurNoeud(VERT));
        actionPoste();
        posteVert2 = true;
      }
      else
      {
        posteVert2 = false;
        posteJaune2 = false;
        posteRouge2 = false;
        posteJaune2 = false;
        essaiDist = 0;
      }
    }
  }
  else
  {
    eteindreDEL(0);
    allumerDEL(4);
    delay(1000);
    int tableau10[8];
    lireSuiveurLigne(tableau10);
    afficherLigne(tableau10);

  }

//  if (ROBUS_IsBumper(0))
//  {
//    leverBras();
//    Serial.println("Haut");

//  }
//   if (ROBUS_IsBumper(1))
//  {
//    baisserBras();
//    Serial.println("Bas");
//  }
//   if (ROBUS_IsBumper(3))
//  {
//    leverBrasDeplacement();
//     Serial.println("Deplacement");

//  }

// loopAjustementServo(BRAS);

}
