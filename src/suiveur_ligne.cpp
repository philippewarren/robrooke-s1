#include "suiveur_ligne.h"

const int pin = 13;

void lireSuiveurLigne(int output [8])
{   
    pinMode(pin,OUTPUT);
    digitalWrite(pin,HIGH);
    //constante
    int const NOMBRE_DE_LECTURE = 3;
    //lecture des donnée
    for(int i = 0; i<8;i++)output[i]=0;
    for (int i=0;i<NOMBRE_DE_LECTURE;i++)
    {
    delay(1);
    output[0] += analogRead(A10);
    output[1] += analogRead(A11);
    output[2] += analogRead(A12);
    output[3] += analogRead(A13);
    output[4] += analogRead(A4);
    output[5] += analogRead(A5);
    output[6] += analogRead(A6);
    output[7] += analogRead(A7);
    }
    digitalWrite(pin,LOW);

    for (int i = 0; i<8; i++)output[i] /= NOMBRE_DE_LECTURE;

}

void suivreLigne(float vitesse)
{

    //lecture des données
    int lectureSuiveurDeLigne [8];
    lireSuiveurLigne(lectureSuiveurDeLigne);
    estLigneHuit(lectureSuiveurDeLigne);

  //calcul des différences entre capteurs opposés
  float delta1 = lectureSuiveurDeLigne[4]-lectureSuiveurDeLigne[3];
  float delta2 = lectureSuiveurDeLigne[5]-lectureSuiveurDeLigne[2];
  float delta3 = lectureSuiveurDeLigne[6]-lectureSuiveurDeLigne[1];
  float delta4 = lectureSuiveurDeLigne[7]-lectureSuiveurDeLigne[0];
  delta1 *= 0.75;
  delta2 *= 1.5;
  delta3 *= 3;
  delta4 *= 9;

  //calcul du facteur de correction
  float facteur = max(max(delta1,delta2),max(delta3, delta4));
  float facteurMin = min(min(delta1,delta2),min(delta3, delta4));
  if (facteurMin*-1 < facteur)syncroroue(vitesse,1/(1+(facteur/3)));
  else syncroroue(vitesse,1-(facteurMin/3));
}

bool detecterLigne()
{
    bool ligneDetecte = false;
    //lecture des données
    int lectureSuiveurDeLigne[8] ;
    lireSuiveurLigne(lectureSuiveurDeLigne);

    //calcule du seuil
    long seuil = (long)CONTRASTE * 0.70;

    //compare les variances 
    for (int i=1;i<8;i++)
    {
        long delta = ((long)lectureSuiveurDeLigne[0]-(long)lectureSuiveurDeLigne[i]);
        if (delta > seuil)
        {
            ligneDetecte = true;
        }
    }

    //si le capteur 1 est défectueux
    for (int i=6;i>-1;i--)
    {
        long delta = ((long)lectureSuiveurDeLigne[7]-(long)lectureSuiveurDeLigne[i]);
        if (delta > seuil)
        {
            ligneDetecte = true;
        }
    }

    //test
    return ligneDetecte;
    
    
}

bool lignePerpendiculaire()
{
  int tableauLigne[8];
  lireSuiveurLigne(tableauLigne);
  estLigneHuit(tableauLigne);
  bool perp = true;
  for (int i = 0; i<8;i++)
  {
    if(tableauLigne[i] <= 0)perp = false;
  }
  return perp;
}

bool avancerDroitLigneBloque(float vitesse, float distance)
{
  float distanceParcourue = 0;
  bool fin = false;

  distance = cmEnClics(distance);
  if(Bob == 'A') distance /= 1;
  else distance /= 1;
  resetDeuxEncodeurs();
  syncroroue (vitesse,1,true);
  if (vitesse * distance < 0)vitesse *= -1;

  while (!fin)
  {
    delay(50);
    distanceParcourue += ENCODER_Read(0);
    suivreLigne(vitesse);
    fin = (distanceParcourue >= distance && distance > 0)||(distanceParcourue <= distance && distance < 0);
  }
  syncroroue (0,1,true);
  return true;
}

bool tournerBloqueSansArret(float vitesse, float angle)
{
  float distanceParcourue = 0;
  bool fin = false;

  if(Bob == 'A') angle -
  3;
  else angle /= 1;
  float distance = cmEnClics((19 * 3.14160) / 360 * angle);
  resetDeuxEncodeurs();
  if (vitesse * angle < 0)vitesse *= -1;

  while (!fin)
  {
    delay(30);
    distanceParcourue += ENCODER_Read(1);
    syncroroue(vitesse,-1);
    fin = (distanceParcourue >= distance && distance > 0)||(distanceParcourue <= distance && distance < 0);
  }
  return true;
}

bool centrerLigne(float angleVue = 30)
{
  int nbrValeur =angleVue*2;
  int valeur[nbrValeur];
  int lecture[8];
  int i = 0;
  
  syncroroue (0.2,-1,true);
  tournerBloque(0.2,angleVue);
  while (i< nbrValeur)
  {
    lireSuiveurLigne(lecture);
    int donnee = lecture[3]+lecture[4]+lecture[2]*0.5+lecture[5]*0.5;
    tournerBloqueSansArret(0.2,-1);
    valeur[i]=donnee;
    i++;
  }
  
  syncroroue (0,-1,true);
  int max = 0;
  i = 1;
  while (i<nbrValeur)
  {
    if(valeur[i]>valeur[max])max = i;
    i++;
  }
  tournerBloque(0.3,5*(nbrValeur - max));
  return true;
}

void estLigneHuit(int lectures[8])
{
  for (int i=0; i<8; i++)
  {
    lectures[i] = (lectures[i] >= 650) ? 1 : /*(lectures[i] > 250) ? 2 :*/ 0;//(350 rouge ok; vert ok; problème vert?)
  }
}

void trouverLigne(int sensDeRotation)
{
  int sens = (sensDeRotation==0) ? 1 : -1;
  int indexSens = (sensDeRotation==0) ? CAPTEUR_GAUCHE : CAPTEUR_DROIT;
  float vitesse = 0.2;
  int lectures[8];
  int CLICS_180_DEGRES = cmEnClics(largeurEss*PI);
  bool capteurInverseVu = false;
  bool aTrouveLigne = false;

  changerVitesseMoteur(sensDeRotation, vitesse);
  while (!aTrouveLigne && ENCODER_Read(sensDeRotation)<CLICS_180_DEGRES)
  {
    lireSuiveurLigne(lectures);
    estLigneHuit(lectures);

    if (lectures[indexSens+sens*2]>=1) capteurInverseVu = true;
    if (lectures[indexSens]>=1 && capteurInverseVu) aTrouveLigne = true;

    // for (int i=0; i<8; i++)
    // {
    //   if (lectures[i]>=1) aTrouveLigne = true;
    // }
  }
  arreterDeuxMoteurs();
  return;
}

void afficherLigne(int ligne[8])
{
  for(int i = 0; i<8;i++)
  {
    Serial.print(ligne[i]);
    Serial.print('\t');
  }
  Serial.print('\n');
}

bool estSorti(bool reset = false)
{
  //lecture des données
    int lectureSuiveurDeLigne[8];
    lireSuiveurLigne(lectureSuiveurDeLigne);
    estLigneHuit(lectureSuiveurDeLigne);

    //Arrête s'il sort des lignes
    const int SEUIL_AVOIR_LIGNE = 5;
    const int SEUIL_PERTE_LIGNE = 20;

    static int avaitUneLigne = 0;
    static int aPerduLigne = 0;
    bool pasLigne;

    if (reset)
    {
      avaitUneLigne = 0;
      aPerduLigne = 0;
      return false;
    }

    if (avaitUneLigne<SEUIL_AVOIR_LIGNE) 
    {
      for (int ligne: lectureSuiveurDeLigne)
      {
        if (ligne==1)
        {
          avaitUneLigne++;
        }
      }
      if (avaitUneLigne>SEUIL_AVOIR_LIGNE) avaitUneLigne=SEUIL_AVOIR_LIGNE;
    }

  if (avaitUneLigne==SEUIL_AVOIR_LIGNE)
  {
    pasLigne = true;
    for (int ligne: lectureSuiveurDeLigne)
    {
      if (ligne==1)
      {
        pasLigne = false;
      }
    }
    if (pasLigne) aPerduLigne++; 
  }

  if (aPerduLigne>SEUIL_PERTE_LIGNE)
  {
    avaitUneLigne=0;
    aPerduLigne=0;
    return true;
  }
  
  return false;
}

void traquerLigneBloque(float vitesse)
{
  syncroroue(vitesse,1,true);
  while (!lignePerpendiculaire())
  {
    suivreLigne(vitesse);
    if (estSorti())
    {
      changerVitesseDeuxMoteurs(0);
      bouton=3;
      break;
    }
    delay(10);
  }
  estSorti(true);
  syncroroue(0,1,true);
}