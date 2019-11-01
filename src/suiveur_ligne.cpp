#include "suiveur_ligne.h"

void lireSuiveurLigne(int output [8])
{
    const int pin = 13;
    pinMode(pin,OUTPUT);
    digitalWrite(13,HIGH);
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

    //calcul des différences entre capteurs opposés
    float delta1 = lectureSuiveurDeLigne[3]-lectureSuiveurDeLigne[4];
    float delta2 = lectureSuiveurDeLigne[2]-lectureSuiveurDeLigne[5];
    float delta3 = lectureSuiveurDeLigne[1]-lectureSuiveurDeLigne[6];
    float delta4 = lectureSuiveurDeLigne[0]-lectureSuiveurDeLigne[7];

    //calcul du facteur de correction
    float facteur = delta1*1 + delta2 * 2+ delta3 * 3+ delta4 * 4;
    if (facteur > 4*CONTRASTE) facteur = 4*CONTRASTE;
    else if (facteur < -4*CONTRASTE) facteur = -4*CONTRASTE;
    facteur = facteur / (6 * CONTRASTE);

    //modification de la vitesse des roues
    float factVit = facteur;
    if(factVit<0)factVit *= -1;
    factVit = 1 -factVit*0.7;
    if(vitesse < 0)facteur *= -1;
    syncroroue(vitesse*factVit,(1+facteur));

}

bool detecterLigne()
{
    bool ligneDetecte = false;
    //lecture des données
    int lectureSuiveurDeLigne[8] ;
    lireSuiveurLigne(lectureSuiveurDeLigne);

    //calcule du seuil
    long seuil = (long)CONTRASTE * 0.50;
    seuil *= seuil  ;

    //calcule de la somme des variances au carrée
    for (int i=1;i<8;i++)
    {
        long delta = ((long)lectureSuiveurDeLigne[0]-(long)lectureSuiveurDeLigne[i]);
        if (delta*delta > seuil)
        {
            ligneDetecte = true;
        }
    }

    //test
    return ligneDetecte;
    
    
}

bool traquerLigne(float vitesse)
{
    //2 static
    static bool ligne = false;
    static bool timerLance = false;
    static bool timer = 0;

    bool retour = false;

    if(detecterLigne())
    {
       ligne = true;
       timerLance = false;
    }
    else if(ligne)
    {
        if (!timerLance)
        {
        timerLance = true;
        timer = millis();
        }
         //si aucune ligne n'est détecter durant 0.300s, arret de la séquence
        else if ((millis()-timer)>300/vitesse)
        {
        timerLance = false;
        ligne = false;
        retour = true;
        syncroroue(0,1,true);
        }
    }
    if (ligne)
    {
        suivreLigne(vitesse);
    }
    else if(retour == false)
    {
        syncroroue(vitesse);
    }

    
    
    return retour;
  
}

bool avancerDroitLigne(float vitesse, float distance)
{
  static float distanceParcourue = 0;
  static long timer = millis();
  static bool reset = true;
  static bool resetEnc = false;
  static float ancEnc = 0;

  if (distance == 0)
    return true;
  else
  {
    if (vitesse*distance < 0)vitesse *= -1;

    if(Bob == 'A') distance /= 1.175;
    else distance /= 1.05;

    float enc = clicsEnCm(ENCODER_Read(0));

    if (reset)
    {
      timer = millis();
      ancEnc = clicsEnCm(ENCODER_Read(0));
      reset = false;
    }

    distanceParcourue += enc - ancEnc;

    if (resetEnc)
    {
      distanceParcourue += ancEnc;
      resetEnc = false;
    }

    ancEnc = enc;


    if ((distanceParcourue >= distance && distance > 0)||(distanceParcourue <= distance && distance < 0))
    {
      distanceParcourue = 0;
      syncroroue(0, 1, true);
      return true;
    }
    else
    {
      if (millis() - timer > 50)
      {
        suivreLigne(vitesse);
        resetEnc = true;
        timer = millis();
      }
      return false;
    }
  }
}