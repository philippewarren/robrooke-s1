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
    float delta1 = ((float)lectureSuiveurDeLigne[3]*lectureSuiveurDeLigne[3])-((float)lectureSuiveurDeLigne[4]*lectureSuiveurDeLigne[4]);
    float delta2 = ((float)lectureSuiveurDeLigne[2]*lectureSuiveurDeLigne[2])-((float)lectureSuiveurDeLigne[5]*lectureSuiveurDeLigne[5]);
    float delta3 = ((float)lectureSuiveurDeLigne[1]*lectureSuiveurDeLigne[1])-((float)lectureSuiveurDeLigne[6]*lectureSuiveurDeLigne[6]);
    float delta4 = ((float)lectureSuiveurDeLigne[0]*lectureSuiveurDeLigne[0])-((float)lectureSuiveurDeLigne[7]*lectureSuiveurDeLigne[7]);

    //calcul du facteur de correction
    float facteur = delta1*0.5 + delta2 * 1+ delta3 * 2+ delta4 * 6;
    if (facteur > 4*(float)CONTRASTE*(float)CONTRASTE) facteur = 4*(float)CONTRASTE*(float)CONTRASTE;
    else if (facteur < -4*CONTRASTE*CONTRASTE) facteur = -4*CONTRASTE*CONTRASTE;
    facteur = facteur / (4 * (float)CONTRASTE*(float)CONTRASTE);

    //modification de la vitesse des roues
    float factVit = facteur;
    if(factVit<0)factVit *= -1;
    factVit = 1 -factVit*0.5;
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
        distanceParcourue = 0;
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
      reset = true;
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



bool tournerNoir(float vitesse,int nbrLigne)
{
    static bool reset = true;
    static int ligne = 0;
    static bool sur = false;
    bool retour = false;
    if (reset)
    {
        syncroroue(vitesse,-0.8,true);
        ligne = 0;
        reset = false;
        sur = false;
    }
    else
    {
        syncroroue(vitesse,-1);
        int lecture[8];
        lireSuiveurLigne(lecture);
        if (lecture[4]>600 && lecture[5]>600)
        {
            if(!sur)
            {
                sur = true;
                ligne += 1;
                if(ligne >= nbrLigne)
                {
                    syncroroue(0,1,true);
                    reset = true;
                    retour = true;
                }
            }
        }
        else sur = false;

    }
    return retour;
    

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
  int nbrValeur =(angleVue * 2) / 5;
  int valeur[nbrValeur];
  int lecture[8];
  int i = 0;
  
  syncroroue (0.3,-1,true);
  tournerBloque(0.3,angleVue);
  while (i< nbrValeur)
  {
    lireSuiveurLigne(lecture);
    int donnee = lecture[3]+lecture[4]+lecture[2]*0.1+lecture[5]*0.1;
    tournerBloqueSansArret(0.3,-5);
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

void lireSuiveurLigneDeuxCapteurs(int deuxLectures[2])
{
  int lectures[8];
  lireSuiveurLigne(lectures);
  deuxLectures[0] = lectures[2];
  deuxLectures[1] = lectures[5];
}

void estLigne(int lectures[2])
{
  lectures[0] = (lectures[0] > 400) ? 1 : (lectures[0] > 250) ? 2 : 0;
  lectures[1] = (lectures[1] > 400) ? 1 : (lectures[1] > 250) ? 2 : 0;
}

void estLigneHuit(int lectures[8])
{
  for (int i=0; i<8; i++)
  {
    lectures[i] = (lectures[i] >= 400) ? 1 : /*(lectures[i] > 250) ? 2 :*/ 0;//(350 rouge ok; vert ok; problème vert?)
  }
}

void suivreLigneSimple(float DISTANCE, float VITESSE = 0.3)
{
  int deuxLectures[2];
  long long clicsTotaux = cmEnClics(DISTANCE);
  float vitesseG = VITESSE;
  float vitesseD = VITESSE;
  int estFinLigne = 0;

  const int DT = 5; //délais du cycle

  bool ligneAuCentre = false;

  resetDeuxEncodeurs();

  while (ENCODER_Read(0)<clicsTotaux && estFinLigne<3)
  {
    lireSuiveurLigneDeuxCapteurs(deuxLectures);
    estLigne(deuxLectures);

    changerVitesseDeuxMoteurs(vitesseG, vitesseD);
    delay(DT);

    //Commenter ce if.. pour tourner en rond quand il voit pas de ligne, ce qui facilite leur recherche
    if (deuxLectures[0]==deuxLectures[1])
    {
      changerVitesseDeuxMoteurs(VITESSE, VITESSE);
    }
    if (deuxLectures[0] >= 1 && deuxLectures[1] >= 1)
    {
      estFinLigne++;
    }
    else if (deuxLectures[1]==1) //Capteur de gauche == ligne
    {
      changerVitesseDeuxMoteurs(0, 0.2);
      // vitesseD = vitesseD-0.02;
      // changerVitesseMoteur(1, vitesseD);
      // delay(500);
    }
    else if (deuxLectures[0]==1)   //Capteur de droite == ligne
    {
      changerVitesseDeuxMoteurs(0.2, 0);
      // vitesseD = vitesseD+0.02;
      // changerVitesseMoteur(1, vitesseD);
      // delay(500);
    }
  }
  arreterDeuxMoteurs();
  resetDeuxEncodeurs();
}

void suivreLigneSimpleHuit(float DISTANCE, float VITESSE = 0.3)
{
  int huitLectures[8];
  long long clicsTotaux = cmEnClics(DISTANCE);
  float vitesseG = VITESSE;
  float vitesseD = VITESSE;
  int estFinLigne = 0;
  int estPasLigneCentre = 0;
  int estLigneCentre = 0;
  int directionRotation = 0;

  int CLICS_360_DEGRES = cmEnClics(largeurEss*2*PI);

  const int DT = 5; //délais du cycle

  bool ligneAuCentre = false;

  resetDeuxEncodeurs();

  while (ENCODER_Read(0)<clicsTotaux && estFinLigne<10)
  {
    lireSuiveurLigne(huitLectures);
    estLigneHuit(huitLectures);

    changerVitesseDeuxMoteurs(vitesseG, vitesseD);
    delay(DT);

    if(huitLectures[3]>=1 || huitLectures[4]>=1)
    {
      estLigneCentre++;
    }
    else
    {
      estPasLigneCentre ++;
    }
    if (estPasLigneCentre>30)
    {
      ligneAuCentre = false;
      estPasLigneCentre = 0;
    }
    else if (estLigneCentre>30)
    {
      ligneAuCentre = true;
      estLigneCentre = 0;
    }

    if (ligneAuCentre)
    {
      //Commenter ce if.. pour tourner en rond quand il voit pas de ligne, ce qui facilite leur recherche
      if (huitLectures[CAPTEUR_DROIT]==huitLectures[CAPTEUR_GAUCHE])
      {
        vitesseG = VITESSE;
        vitesseD = VITESSE;
      }
      if (huitLectures[CAPTEUR_DROIT] >= 1 && huitLectures[CAPTEUR_GAUCHE] >= 1)
      {
        estFinLigne++;
      }
      else if (huitLectures[CAPTEUR_GAUCHE]==1) //Capteur de gauche == ligne
      {
        // changerVitesseDeuxMoteurs(0, 0.2);
        vitesseG = 0;
        vitesseD = 0.2;
        // vitesseD = vitesseD-0.02;
        // changerVitesseMoteur(1, vitesseD);
        // delay(500);
      }
      else if (huitLectures[CAPTEUR_DROIT]==1)   //Capteur de droite == ligne
      {
        // changerVitesseDeuxMoteurs(0.2, 0);
        vitesseG = 0.2;
        vitesseD = 0;
        // vitesseD = vitesseD+0.02;
        // changerVitesseMoteur(1, vitesseD);
        // delay(500);
      }
    }
    else
    {
      if (huitLectures[CAPTEUR_DROIT] >= 1 && directionRotation!=-1)
      {
        // changerVitesseDeuxMoteurs(-0.2, 0.2);
        vitesseG = 0;
        vitesseD = 0.2;
        directionRotation = 1;
      }
      else if (huitLectures[CAPTEUR_GAUCHE] >= 1 && directionRotation!=1)
      {
        // changerVitesseDeuxMoteurs(0.2, -0.2);
        vitesseG = 0.2;
        vitesseD = 0;
        directionRotation = -1;
      }
    }
  }
  arreterDeuxMoteurs();
  resetDeuxEncodeurs();
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

void traquerLigneBloque(float vitesse)
{
  syncroroue(vitesse,1,true);
  bool fin = false;
  int iteration = 0;
  while (!fin)
  {
    if (!detecterLigne)iteration = 0;
    else iteration += 1;
    if (iteration > 2) fin = true;
    syncroroue(vitesse,1);
    delay(30);
  }
  fin = false;
  iteration = 0;
  centrerLigne(20);
  while (!fin)
  {
    if (detecterLigne)iteration = 0;
    else iteration += 1;
    if (iteration > 2) fin = true;
    suivreLigne(vitesse);
    delay(30);
  }
  syncroroue(0,1,true);
  
}