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


void estLigneHuit(int lectures[8])
{
  for (int i=0; i<8; i++)
  {
    lectures[i] = (lectures[i] >= 650) ? 1 : /*(lectures[i] > 250) ? 2 :*/ 0;//(350 rouge ok; vert ok; problème vert?)
  }
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

<<<<<<< HEAD
<<<<<<< HEAD
=======
bool estSorti()
=======
bool estSorti(bool reset = false)
>>>>>>> fb903c61bc1214fe73ea2aa1f441d488e036cb67
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

>>>>>>> 1dc4c9b046dc3a5af2e7abe2d4d272f693dbef98
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