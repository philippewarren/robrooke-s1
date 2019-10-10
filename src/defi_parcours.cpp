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
#include <EEPROM.h>

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces

//float sequence[50];

// CECI EST LE DEV PUSH DANS MASTER

const int DELAIS_POST_OPERATION = 300;

char Robot = 'I';
const double CLICS_PAR_CM = 3200/(2.54*3*PI);
const uint8_t gauche = 0;
const uint8_t droite = 1;

const float diaRoue = 7.6;                           //diametre de la roue en cm
const float largeurEss = Robot=='A' ? 18.2 : 18.1;   //distance entre les roues en cm
const float largeurParc = 45;                        //largeur du parcours en cm
const float TAN_22_5 = 0.414213562;                  //le tan de 22.5 (utile pour la rotation)
const float DIST_90 = (largeurParc-largeurEss)/2;    //la distance que Bob doit avancer pour un virage de 90 degres
const float DIST_45 = DIST_90*TAN_22_5;              //la distance que Bob doit avancer pour un virage de 45 degres

const float VITESSE_PREPOST_ROTATION = 0.2;          //la vitesse avant et apres les rotations

long pulse180 = 0;                                   

long pulseD = 0;
long pulseG = 0;

/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void determinerRobot()
{
    Robot = EEPROM.read(0);
}

double clicsEnCm(long nbClics)
{
  return nbClics/CLICS_PAR_CM;
}

long long cmEnClics(float nbCm)
{
  return (long long)(nbCm*CLICS_PAR_CM);
}

void resetDeuxEncodeurs()
{
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  return;
}

void changerVitesseMoteur(uint8_t moteur, float nouvelleVitesse)
{
  /*int32_t ancienneVitesseEnClics = ENCODER_Read(moteur);
  if ((ancienneVitesseEnClics<0 && nouvelleVitesse>0) || (ancienneVitesseEnClics>0 && nouvelleVitesse<0) || ancienneVitesseEnClics==0)
  {
    MOTOR_SetSpeed(moteur, 0);
    delay(25);
    MOTOR_SetSpeed(moteur, nouvelleVitesse);
  }
  else*/ MOTOR_SetSpeed(moteur, nouvelleVitesse);
  return;
}

void changerVitesseDeuxMoteurs(float vitesseG, float vitesseD)
{
  changerVitesseMoteur(0,vitesseG);
  changerVitesseMoteur(1,vitesseD);
  return;
}

void arreterDeuxMoteurs()
{
  changerVitesseDeuxMoteurs(0,0);
  return;
}

void avancer(float distanceEnCm)
{
  float deltaBob = Robot=='A' ? -0.025 : -0.025;
  float delta = distanceEnCm>0 ? deltaBob : -deltaBob;
  static float vitesseG = distanceEnCm>0 ? 0.4 : -0.4;
  static float vitesseD = vitesseG - delta;

  static float vitesseGPre = 2*vitesseG;
  static float vitesseDPre = 2*vitesseD;

  long clicsG = 0;
  long clicsD = 0;
  bool estRalenti = false;
  bool estAccelere = true;

  const float FACTEUR_P = 5E-2;  //4E-2; 7E-2
  const float FACTEUR_I = 5E-4;  //5E-5; 5E-4
  const float FACTEUR_D = 1.8E-5;   //1.7E-5; 1.8E-4
  const int TEMPS = 200;          //temps en microsecondes

  static float erreur = 0;
  long long cumulClics = 0;
  static float derniereErreur = 0;
  static float integrale = 0;  
  static float differentielle = 0;

  int i=0;
  int nb=100;
  int vitesseDebugG[nb];
  int vitesseDebugD[nb];
  int erreurDebug[nb];
  int integraleDebug[nb];
  int differentielleDebug[nb];
  float correctionDebug[nb];

  estRalenti = false;
  estAccelere = true;
  vitesseG=0.5*vitesseGPre;
  vitesseD=0.5*vitesseDPre;

	do
  {
		resetDeuxEncodeurs();
		
		changerVitesseDeuxMoteurs(vitesseG,vitesseD);
		
		delay(TEMPS);
    clicsG = (long)ENCODER_Read(0);
		clicsD = (long)ENCODER_Read(1);
    cumulClics+=clicsG;
    
		Serial.print("G: ");
    Serial.print(clicsG);
    Serial.print(" et D: ");
    Serial.print(clicsD);
    Serial.println();

	  erreur=(double)clicsG/TEMPS-(double)clicsD/TEMPS;
    integrale+=erreur;
    differentielle=erreur-derniereErreur;
    erreurDebug[i]=100000000*erreur*FACTEUR_P;
    vitesseDebugG[i]=1000*vitesseG;
    vitesseDebugD[i]=1000*vitesseD;
    integraleDebug[i]=100000000*integrale*FACTEUR_I;
    differentielleDebug[i]=100000000*differentielle*FACTEUR_D;
    correctionDebug[i]=FACTEUR_P*erreur+FACTEUR_I*integrale+FACTEUR_D*differentielle;
    i++;
	  vitesseD=vitesseD+FACTEUR_P*erreur+FACTEUR_I*integrale+FACTEUR_D*differentielle;
		changerVitesseMoteur(1,vitesseD);

    derniereErreur=erreur;

    if (!estRalenti)
    {
      vitesseGPre=vitesseG;
      vitesseDPre=vitesseD;
    }

    if (vitesseG >= 0.70) estAccelere=false;

    if (estAccelere)
    {
      vitesseG*=1.1;
      vitesseD*=1.1;
      changerVitesseDeuxMoteurs(vitesseG, vitesseD);
    }

    if (cumulClics > cmEnClics(distanceEnCm-20))
    {
      estRalenti=true;
      estAccelere=false;
      //vitesseG*=0.8;
      //vitesseD*=0.8;
      //changerVitesseDeuxMoteurs(vitesseG, vitesseD);
      changerVitesseDeuxMoteurs(0.4, 0.4*vitesseD/vitesseG);
    }
  }
	while (cumulClics < cmEnClics(distanceEnCm));

	arreterDeuxMoteurs();

  //while (!ROBUS_IsBumper(0)) ;
  int nombre=i;
  i=0;
  Serial.println("Début des vitesses");
  for (i=0; i<nombre; i++)
  {
   // Serial.println(erreurDebug[i]);
   // Serial.println(integraleDebug[i]);
   // Serial.println(differentielleDebug[i]);
    Serial.print("G: ");
    Serial.print(vitesseDebugG[i]);
    Serial.print(" et D: ");
    Serial.print(vitesseDebugD[i]);
    Serial.println();
  }

 // while (!ROBUS_IsBumper(1)) ;
  i=0;
  Serial.println("Début des erreur");
  for (i=0; i<nombre; i++)
  {
   // Serial.println(erreurDebug[i]);
   // Serial.println(integraleDebug[i]);
   // Serial.println(differentielleDebug[i]);
    Serial.print("P: ");
    Serial.print(erreurDebug[i]);
    Serial.print(" et I: ");
    Serial.print(integraleDebug[i]);
    Serial.print(" et D: ");
    Serial.print(differentielleDebug[i]);
    Serial.print(" pour une corr de: ");
    Serial.print(100000*correctionDebug[i]); 
    Serial.println();
  }
  delay(20);
  return;
}

void avancerVitesseFixe(float distanceEnCm, float vitesseBase = 0.3)
{
  float deltaBob = Robot=='A' ? -0.025 : -0.050;
  float delta = (distanceEnCm)>0 ? deltaBob : -deltaBob;
  static float vitesseG = distanceEnCm>0 ? vitesseBase : -vitesseBase;
  static float vitesseD = vitesseG - delta;

  long clicsG = 0;
  long clicsD = 0;

  const float FACTEUR_P = 5E-2;  //4E-2; 7E-2
  const float FACTEUR_I = 5E-4;  //5E-5; 5E-4
 // const float FACTEUR_D = 1.8E-5;   //1.7E-5; 1.8E-4
  const int TEMPS = 50;          //temps en microsecondes

  static float erreur = 0;
  long long cumulClics = 0;
 // static float derniereErreur = 0;
  static float integrale = 0;  
 // static float differentielle = 0;

 /* bool estRalenti = false;
  vitesseG=0.5*vitesseGPre;
  vitesseD=0.5*vitesseDPre;*/

  int i=0;
  int nb=100;
  int vitesseDebugG[nb];
  int vitesseDebugD[nb];
  int erreurDebug[nb];
  int integraleDebug[nb];
 // int differentielleDebug[nb];
  float correctionDebug[nb];

  resetDeuxEncodeurs();
  changerVitesseDeuxMoteurs(vitesseG,vitesseD);

	do
  {	
		delay(TEMPS);
    clicsG = (long)ENCODER_ReadReset(0);
		clicsD = (long)ENCODER_ReadReset(1);
    cumulClics+=clicsG;
    
		/*Serial.print("G: ");
    Serial.print(clicsG);
    Serial.print(" et D: ");
    Serial.print(clicsD);
    Serial.println();*/

	  erreur=(double)clicsG/TEMPS-(double)clicsD/TEMPS;
    integrale+=erreur;
    //differentielle=erreur-derniereErreur;
    erreurDebug[i]=100000000*erreur*FACTEUR_P;
    vitesseDebugG[i]=1000*vitesseG;
    vitesseDebugD[i]=1000*vitesseD;
    integraleDebug[i]=100000000*integrale*FACTEUR_I;
    //differentielleDebug[i]=100000000*differentielle*FACTEUR_D;
    correctionDebug[i]=FACTEUR_P*erreur+FACTEUR_I*integrale;//+FACTEUR_D*differentielle;
    i++;
	  vitesseD=vitesseD+FACTEUR_P*erreur+FACTEUR_I*integrale;//+FACTEUR_D*differentielle;
		changerVitesseMoteur(1,vitesseD);

    //derniereErreur=erreur;

   /* if (!estRalenti)
    {
      vitesseGPre=vitesseG;
      vitesseDPre=vitesseD;
    }

    if (cumulClics > cmEnClics(distanceEnCm-10))
    {
      estRalenti=true;
    //  vitesseG*=0.8;
    //  vitesseD*=0.8;
    //  changerVitesseDeuxMoteurs(vitesseG, vitesseD);
      changerVitesseDeuxMoteurs(0.4, 0.4*vitesseD/vitesseG);
    }*/
  }
	while (cumulClics < cmEnClics(distanceEnCm));

	arreterDeuxMoteurs();

  //while (!ROBUS_IsBumper(0)) ;
  int nombre=i;
  i=0;
  /*Serial.println("Début des vitesses");
  for (i=0; i<nombre; i++)
  {
   // Serial.println(erreurDebug[i]);
   // Serial.println(integraleDebug[i]);
   // Serial.println(differentielleDebug[i]);
    Serial.print("G: ");
    Serial.print(vitesseDebugG[i]);
    Serial.print(" et D: ");
    Serial.print(vitesseDebugD[i]);
    Serial.println();
  }

 // while (!ROBUS_IsBumper(1)) ;
  i=0;
  Serial.println("Début des erreur");
  for (i=0; i<nombre; i++)
  {
   // Serial.println(erreurDebug[i]);
   // Serial.println(integraleDebug[i]);
   // Serial.println(differentielleDebug[i]);
    Serial.print("P: ");
    Serial.print(erreurDebug[i]);
    Serial.print(" et I: ");
    Serial.print(integraleDebug[i]);
    Serial.print(" et D: ");
    //Serial.print(differentielleDebug[i]);
    Serial.print(" pour une corr de: ");
    Serial.print(100000*correctionDebug[i]); 
    Serial.println();
  }*/
  delay(DELAIS_POST_OPERATION);
  return;
}

///initialisation des constantes
void initRot()
{
  pulse180 = largeurEss*1600/diaRoue;
 // Serial.println(pulse180);
}
///lecture d'encodeur avec stockage
int readResetKeepDroit()
{
  int out = ENCODER_ReadReset(droite);
  pulseD += out;
  return out;
}
int readResetKeepGauche()
{
  int out = ENCODER_ReadReset(gauche);
  pulseG += out;
  return out;
}
///rotation 180
void DemiTour()
{

  const float vitesseRotation = 0.25;

  float correction = 1;
  pulseD = 0;
  pulseG = 0;

  delay(300);

  resetDeuxEncodeurs();
  MOTOR_SetSpeed(droite,vitesseRotation);
  MOTOR_SetSpeed(gauche,-vitesseRotation);
  delay(100);
  correction = -float(readResetKeepDroit())/float(readResetKeepGauche());
  MOTOR_SetSpeed(gauche,vitesseRotation/correction);
  while (pulseD < pulse180)
  {
    delay(10);
    correction = float(readResetKeepDroit())/(-float(readResetKeepGauche())/correction);
    MOTOR_SetSpeed(gauche,-vitesseRotation*correction);
  //  Serial.println(correction);
  //  Serial.println(pulseD);
  }
  arreterDeuxMoteurs();
  delay(1/2 * DELAIS_POST_OPERATION);
}

void rot(int Nbr45 = 1, bool direction = 1)
{

  const float vitesseRotation = 0.4;

  resetDeuxEncodeurs();
  int roue = gauche;
  if (!direction) roue = droite;
  arreterDeuxMoteurs();
  long clic = pulse180 / 2 * Nbr45;
  MOTOR_SetSpeed(roue,vitesseRotation);
  long pulseTotal = 0;
  while (pulseTotal < clic)
  {
    delay(30);
    pulseTotal += ENCODER_ReadReset(roue);
  }
  arreterDeuxMoteurs();
  delay(DELAIS_POST_OPERATION);
}

void rot45(bool direction)
{
  avancerVitesseFixe(DIST_45,VITESSE_PREPOST_ROTATION);
  rot(1,direction);
  avancerVitesseFixe(DIST_45, VITESSE_PREPOST_ROTATION);
  return;
}

void rot90(bool direction)
{
  avancerVitesseFixe(DIST_90, VITESSE_PREPOST_ROTATION);
  rot(2,direction);
  avancerVitesseFixe(DIST_90, VITESSE_PREPOST_ROTATION);
  return;
}

void rot135(bool direction)
{
  rot90(direction);
  rot45(direction);
  return;
}

void rot180(bool direction)
{
  rot90(direction);
  rot90(direction);
  return;
}
int determinerAngle(float angle)
{
  if (angle<-179)return -4;
  else if (angle<-134)return -3;
  else if (angle<-89)return -2;
  else if (angle<-44)return -1;
  else if (angle<46)return 1;
  else if (angle<91)return 2;
  else if (angle<136)return 3;
  else return 4;
  
}
void lancerSequence(float sequence[])
{
  int etape;
  int taille = 11; //sequence.getLenght();//sizeof(*sequence)/sizeof(float);
  Serial.println(taille);
  bool rotation = false;
  for (etape=0; etape<taille; etape++)
  {
    Serial.println("Index (étape) # ");
    Serial.println(etape);
    if (rotation)
    {
      Serial.println("Rotation");
      int angle = determinerAngle(sequence[etape]);
      if (angle < 0) rot(-angle,0);
      else rot(angle,1);
      rotation = false;
    }
    else
    {
      float distance = sequence[etape];
      if (etape != 0)
      {
        int angle = determinerAngle(sequence[etape-1]);
        if (angle == 1 || angle == -1||angle ==3 ||angle == -3)distance+=DIST_45;
        else distance += DIST_90;
      }
      if (etape+1 != taille )
      {
        int angle = determinerAngle(sequence[etape+1]);
        if (angle == 1 || angle == -1)distance+=DIST_45;
        else distance += DIST_90;
      }
      Serial.println("Avancer de ");
      Serial.println(distance);
      avancerVitesseFixe(distance);
      rotation = true;
    }

  }
  Serial.println("Demi-tour");
  DemiTour();
  rotation = false;
  for (etape=taille-1; etape>=0; etape--)
  {
    Serial.println("Index (étape) # ");
    Serial.println(etape);
    if (rotation)
    {
      Serial.println("Rotation");
      int angle = determinerAngle(sequence[etape]);
      if (angle < 0) rot(-angle,1);
      else rot(angle,0);
      rotation = false;
    }
    else
    {
      float distance = sequence[etape];
      if (etape+1 != taille)
      {
        int angle = determinerAngle(sequence[etape+1]);
        if (angle == 1 || angle == -1||angle ==3 ||angle == -3)distance+=DIST_45;
        else distance += DIST_90;
      }
      if (etape != 0 )
      {
        int angle = determinerAngle(sequence[etape-1]);
        if (angle == 1 || angle == -1)distance+=DIST_45;
        else distance += DIST_90;
      }
      Serial.println("Avancer de ");
      Serial.println(distance);
      avancerVitesseFixe(distance);
      rotation = true;
    }

  }
}
/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
  determinerRobot();
  initRot();
  Serial.println(largeurEss);
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop()
{
  if (ROBUS_IsBumper(3))
  {
    /*Serial.println("Ceci est le test isBumper(3)");
    Serial.println("Début avancer");
    avancerVitesseFixe(20);
    Serial.println("Fin avancer, début rotation");
    Rot(1,1);
    Serial.println("Fin rotation, début avancer");
    avancerVitesseFixe(50);
    Serial.println("Fin avancer, début rotation");
    DemiTour();
    avancerVitesseFixe(100);
    Rot(2);
    Serial.println("Fin rotation");*/
    rot180(0);
    delay(2000);
    rot180(1);
  }

   if (ROBUS_IsBumper(2))
  {
    const int NBR_SEQ = 11;
    Serial.println("Ceci est le test isBumper(2)");
    float sequence[]=
    {
      100,-90,
      45,90,
      65,45,
      150,-90,
      26,45,
      125
    };
    lancerSequence(sequence);
    /*avancerVitesseFixe(100);
    rot90(0);
    avancerVitesseFixe(45);
    rot90(1);
    avancerVitesseFixe(65);
    rot45(1);
    avancerVitesseFixe(150);
    rot90(0);
    avancerVitesseFixe(26);
    rot45(1);
    avancerVitesseFixe(100);
    DemiTour();*/
  }

   if (ROBUS_IsBumper(1))
  {
    Serial.println("Ceci est le test isBumper(0");
  }

   if (ROBUS_IsBumper(0))
  {
    Serial.println("Ceci est le test isBumper(1)");
    DemiTour();
    
  }

  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
}
